#include "GlfwGeneral.hpp"

using namespace vulkan;

int main() {
    if (!InitializeWindow({ 1280,720 }))
        return -1;//����������ķ���ֵ

    fence fence; //����λ״̬����դ��
    semaphore semaphore_imageIsAvailable;
    semaphore semaphore_renderingIsOver;
    commandBuffer commandBuffer;
    commandPool commandPool(graphicsBase::Base().QueueFamilyIndex_Graphics(), VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
    commandPool.AllocateBuffers(commandBuffer);

    while (!glfwWindowShouldClose(pWindow)) {
        while (glfwGetWindowAttrib(pWindow, GLFW_ICONIFIED))
            glfwWaitEvents();

        graphicsBase::Base().SwapImage(semaphore_imageIsAvailable);
        commandBuffer.Begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
        /*��Ⱦ��������*/
        commandBuffer.End();

        graphicsBase::Base().SubmitCommandBuffer_Graphics(commandBuffer, semaphore_imageIsAvailable, semaphore_renderingIsOver, fence);
        graphicsBase::Base().PresentImage(semaphore_renderingIsOver);

        glfwPollEvents();
        TitleFps();
        //�ȴ�������fence
        fence.WaitAndReset();
    }
    TerminateWindow();
    return 0;
}