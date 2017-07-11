#ifndef _POLICIES_HPP_
#define _POLICIES_HPP_

namespace balance::policy
{
    class average
    {
    private:
        int begin;
        int end;

    public:
        explicit average(int graph_first, int graph_last)
            :begin(graph_first), end(graph_last)
        {}

        std::pair<int, int> get_graph_range() const
        {
            return {begin, end};
        };
    };

    class real
    {
        
    };
}

#endif
