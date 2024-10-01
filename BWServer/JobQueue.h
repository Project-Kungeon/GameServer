#pragma once
#include "pch.h"

class JobQueue : public std::enable_shared_from_this<JobQueue>
{
public:
    using CallbackType = std::function<void()>;

    JobQueue(boost::asio::io_context& io_context)
        : _strand(asio::make_strand(io_context))
    {}

    void DoAsync(CallbackType&& callback)
    {
        boost::asio::post(_strand, std::move(callback));
    }

    template<typename T, typename Ret, typename... Args>
    void DoAsync(Ret(T::* memFunc)(Args...), Args... args)
    {
        std::shared_ptr<T> owner = std::static_pointer_cast<T>(shared_from_this());
        boost::asio::post(_strand, [owner, memFunc, ...args = std::forward<Args>(args)]() mutable {
            ((*owner).*memFunc)(std::forward<Args>(args)...);
            });
    }

    void DoTimer(uint64_t millisAfter, CallbackType&& callback)
    {
        auto timer = std::make_shared<boost::asio::steady_timer>(_strand.context());
        timer->expires_after(std::chrono::milliseconds(millisAfter));
        timer->async_wait(boost::asio::bind_executor(_strand, [callback = std::move(callback)](const boost::system::error_code& error) {
            if (!error) {
                callback();
            }
            }));
    }

    template<typename T, typename Ret, typename... Args>
    void DoTimer(uint64_t millisAfter, Ret(T::* memFunc)(Args...), Args... args)
    {
        std::shared_ptr<T> owner = std::static_pointer_cast<T>(shared_from_this());
        auto timer = std::make_shared<boost::asio::steady_timer>(_strand.context());
        timer->expires_after(std::chrono::milliseconds(millisAfter));
        timer->async_wait(_strand.wrap([owner, memFunc, timer, ...args = std::forward<Args>(args)](const boost::system::error_code& ec) mutable {
            if (!ec) ((*owner).*memFunc)(std::forward<Args>(args)...);
            }));
    }

private:
    boost::asio::strand<boost::asio::io_context::executor_type> _strand;
};