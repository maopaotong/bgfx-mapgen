#include "Examples.h"
namespace mg
{

    int main(int argc, char **argv)
    {
        fog::Injector injector;

        injector.bindAllImpl<Example, //
                             View0,
                             View1,
                             AllViews, //
                             Entity00, //
                             Entity01, //
                             Entity02,
                             AllRenderables, //
                             Args            //
                             >();
        Example *example = injector.get<Example>();

        return example->run();
    }
};

int main(int argc, char **argv)
{
    return mg::main(argc, argv);
}