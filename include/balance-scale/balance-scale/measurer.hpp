#ifndef _MEASURER_HPP_
#define _MEASURER_HPP_

#include <chrono>
#include <memory>

#include <iostream>

namespace balance
{
    using clock = std::chrono::high_resolution_clock;
    using time_point = std::chrono::time_point<clock>;
    using time_duration = std::chrono::duration< long,
                                                 std::nano >;
    using data_set = std::pair<int, time_duration>;

    class measurer
    {
    private:
        int _N;
        std::shared_ptr<std::optional<data_set>> _data;
        std::optional<time_point> _start;

        inline void set_data(time_point end);

    public:
        inline explicit measurer(std::shared_ptr<std::optional<data_set>> data);
        inline ~measurer();

        inline void start(int N);
        inline void end();
    };

    measurer::
    measurer(std::shared_ptr<std::optional<data_set>> data)
        : _N(0),
          _data(std::move(data)),
          _start({})
    {}

    measurer::
    ~measurer()
    {
        if(!_data)
            set_data(clock::now());
    }

    void
    measurer::
    start(int N)
    {
        _start.emplace(clock::now());
        _N = N;
    }

    void
    measurer::
    end()
    {
        set_data(clock::now());
    }

    void
    measurer::
    set_data(time_point end)
    {
        auto duration = end - _start.value();
        _data->emplace(_N,
                       std::chrono::duration<long,
                       std::nano>(duration));
    }
}
#endif
