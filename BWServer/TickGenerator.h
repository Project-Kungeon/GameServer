#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <chrono>
#include "Room.h"

class TickGenerator
{
private:
    boost::asio::io_context& io_context_;
    boost::asio::strand<boost::asio::io_context::executor_type> strand_;
    boost::asio::steady_timer timer_;
    int ticks_per_second_;
    std::function<void(int)> tick_callback_;
    std::chrono::steady_clock::time_point last_tick_time_;
    int tick_count_;
    std::chrono::steady_clock::time_point start_time_;
    int test = 20000;

public:
    TickGenerator(boost::asio::io_context& io_context, int ticks_per_second)
        : io_context_(io_context),
        strand_(boost::asio::make_strand(io_context)),
        timer_(strand_),
        ticks_per_second_(ticks_per_second),
        tick_count_(0) {}

    void start(std::function<void(int)> callback) {
        tick_callback_ = std::move(callback);
        start_time_ = std::chrono::steady_clock::now();
        last_tick_time_ = start_time_;
        tick();
    }

private:
    void tick() {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_tick_time_).count();

        boost::asio::post(strand_, [this, now, elapsed]() {
            tick_count_++;

            if (tick_callback_) {
                tick_callback_(ticks_per_second_);
            }

            // 쿨타임 감소
            boost::asio::post(io_context_, [this]() {
                GRoom[0]->HandleCoolTime(1000 / ticks_per_second_);
                GRoom[0]->HandleBuffTime(1000 / ticks_per_second_);
                });

            // 실제 틱 레이트 계산 및 출력
            auto elapsed_since_start = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time_).count();
            if (elapsed_since_start >= 1000) {
                double actual_rate = static_cast<double>(tick_count_) / (elapsed_since_start / 1000.0);

                spdlog::debug("Actual tick rate: {} per second", actual_rate);
                // 카운트를 초기화하여 1초마다 새로 계산
                tick_count_ = 0;
                start_time_ = now;
            }

        

            // 다음 틱까지의 대기 시간 계산
            auto target_duration = std::chrono::milliseconds(1000 / ticks_per_second_);
            auto next_tick = last_tick_time_ + target_duration;
            auto wait_duration = next_tick - now;

            if (wait_duration.count() < 0) {
                // 틱이 늦었으면 즉시 다음 틱 실행
                wait_duration = std::chrono::milliseconds(0);
                next_tick = now;
            }

            last_tick_time_ = next_tick;

            // 다음 틱 예약
            timer_.expires_at(next_tick);
            timer_.async_wait(boost::asio::bind_executor(strand_, [this](const boost::system::error_code& error) {
                if (!error) {
                    tick();
                }
                }));
            });

       
    }
};

