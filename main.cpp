#include "CGApplication.h"
#include <iostream>
#include <stdexcept>

//
//// PROYECTO: Project11c
//// DESCRIPCIÓN: Aplicación gráfica que incluye el cálculo de sombras
////              con la técnica de Random sampling.
//
int main()
{
    CGApplication app;

    try
    {
        app.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}