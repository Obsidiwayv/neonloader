#include "katana.hh"

KatanaWindow::KatanaWindow(char *appTitle, KatanaWindowSizes sizes)
    : KWSizes{sizes}
{
    if (!glfwInit())
    {
        this->signal = KatanaAppCodes::STOP;
        return;
    }

    this->window = glfwCreateWindow(sizes.width, sizes.height, appTitle, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        this->signal = KatanaAppCodes::STOP;
        return;
    }

    glfwMakeContextCurrent(window);
    this->signal = KatanaAppCodes::START;
}

int KatanaWindow::SetRenderCallback(KatanaAppCodes (*renderLoop)(KatanaWindow kWindow))
{
    glDisable(GL_BLEND);
    while (!glfwWindowShouldClose(window))
    {
        if (this->signal == KatanaAppCodes::STOP)
        {
            break;
        }
        else if (this->signal == KatanaAppCodes::START)
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            this->signal = renderLoop(*this);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    return 0;
}

void KatanaWindow::SetBackgroundColor(BrushColor brush) 
{
    brush.SetBrushColor();
}

void KatanaWindow::Terminate()
{
    glfwTerminate();
}