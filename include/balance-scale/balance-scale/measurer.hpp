#ifndef _MEASURER_HPP_
#define _MEASURER_HPP_


namespace balance
{
    using clock = std::chrono::high_resolution_clock;
    using time_point = std::chrono::time_point< clock,
					        std::nano >;
    using data_set = std::pair<int, time_point>;


    class measurer
    {
    private:
        int _N;
        std::optional<data_set>& _data;
        std::optional<time_point> _start;

    public:
        inline measurer(std::optional<data_set>&);
        inline ~measurer();

        inline void start(int N);
        inline void end();
    };

    measurer::
    measurer(std::optional<data_set>& data)
        : _N(0),
          _data(data),
          _start({})
    {}

    measurer::
    ~measurer()
    {
        if(!_data)
            _data.emplace(clock::now - _start);
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
        auto duration = clock::now - _start;

        _data.emplace(
            std::make_pair(
                _N,
                std::chrono::duration<std::nano>(duration)));
    }
}

#endif
