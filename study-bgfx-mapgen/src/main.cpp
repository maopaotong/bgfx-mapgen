#include "Examples.h"

namespace mg
{

    int main(int argc, char **argv)
    {
        fog::Injector injector;

        injector.bindAllImpl<Example, //
                             Views,   //
                             Args     //
                             >();
        Example *example = injector.get<Example>();

        return example->run();
    }
};

int main(int argc, char **argv)
{
    return mg::main(argc, argv);
}