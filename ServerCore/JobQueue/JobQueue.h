#pragma once

class JobQueue : public std::enable_shared_from_this<JobQueue>
{
public:
    using CallbackType = std::function<void()>;

    JobQueue(boost::asio::io_context& io_context)
        : _strand(make_strand(io_context))
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


    template<typename T, typename Ret, typename... Args>
    void DoTimer(uint64_t millisAfter, Ret(T::* memFunc)(Args...), Args&&... args)
    {
        //std::shared_ptr<T> owner = std::static_pointer_cast<T>(shared_from_this());
        
        std::weak_ptr<T> weak_owner = std::static_pointer_cast<T>(shared_from_this());
        auto timer = std::make_shared<boost::asio::steady_timer>(_strand);
        timer->expires_after(std::chrono::milliseconds(millisAfter));

        // args...는 std::forward를 이용해 이동 시키고, 람다 내에서는 이를 값으로 캡처
        timer->async_wait(boost::asio::bind_executor(_strand, [weak_owner, memFunc, timer,
            args_tuple = std::make_tuple(std::forward<Args>(args)...)](const boost::system::error_code& error) mutable {
                if (!error) {
                    if (auto owner = weak_owner.lock())
                    {
                        // 나머지 로직
                        // std::apply를 이용하여 tuple로 저장한 인수들을 unpack해서 전달
                        std::apply([&owner, memFunc](auto&&... unpackedArgs) {
                            ((*owner).*memFunc)(std::forward<decltype(unpackedArgs)>(unpackedArgs)...);
                            }, args_tuple);
                    }
                    
                }
            }));
    }

protected:
    boost::asio::strand<boost::asio::io_context::executor_type> _strand;
};