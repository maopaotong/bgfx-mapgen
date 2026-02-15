#pragma once

namespace mg
{

    struct Renderable
    {
        virtual int init() = 0;
        virtual void submit() = 0;
        virtual void destroy() = 0;
    };

    template <typename... Ts>
    struct RenderableTuple
    {

        std::tuple<Ts*...> tuple;

        INJECT(RenderableTuple(Ts*... rs)):tuple(rs...)
        {
        }

        int init()
        {
            int es = 0;
            std::apply([&es, this](Ts *...e)
                       {
                           ([&es, &e]()
                            {
                                int err = e->init();
                                if (err)
                                {
                                    es++;
                                } //
                            }(),
                            ...); //
                       },
                       tuple);
            return es > 0 ? -1 : 0;
        }

        void submit()
        {
            std::apply([](Ts *...e)
                       { (e->submit(), ...); }, tuple);
        }
        void destroy()
        {
            std::apply([](Ts *...e)
                       { (e->destroy(), ...); }, tuple);
        }
    };

};
