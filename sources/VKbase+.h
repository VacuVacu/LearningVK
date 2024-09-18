#pragma once
#include "VKbase.h"
#include "VkFormat.h"

namespace vulkan {
    struct graphicsPipelineCreateInfoPack {
        VkGraphicsPipelineCreateInfo createInfo =
        { VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO };
        std::vector<VkPipelineShaderStageCreateInfo> shaderStages;
        //Vertex Input
        VkPipelineVertexInputStateCreateInfo vertexInputStateCi =
        { VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO };
        std::vector<VkVertexInputBindingDescription> vertexInputBindings;
        std::vector<VkVertexInputAttributeDescription> vertexInputAttributes;
        //Input Assembly
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCi =
        { VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO };
        //Tessellation
        VkPipelineTessellationStateCreateInfo tessellationStateCi =
        { VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO };
        //Viewport
        VkPipelineViewportStateCreateInfo viewportStateCi =
        { VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO };
        std::vector<VkViewport> viewports;
        std::vector<VkRect2D> scissors;
        uint32_t dynamicViewportCount = 1;//��̬�ӿ�/���ò����õ�������vector����˶�̬�ӿںͼ��õĸ��������������ֶ�ָ��
        uint32_t dynamicScissorCount = 1;
        //Rasterization
        VkPipelineRasterizationStateCreateInfo rasterizationStateCi =
        { VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO };
        //Multisample
        VkPipelineMultisampleStateCreateInfo multisampleStateCi =
        { VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO };
        //Depth & Stencil
        VkPipelineDepthStencilStateCreateInfo depthStencilStateCi =
        { VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO };
        //Color Blend
        VkPipelineColorBlendStateCreateInfo colorBlendStateCi =
        { VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO };
        std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachmentStates;
        //Dynamic
        VkPipelineDynamicStateCreateInfo dynamicStateCi =
        { VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO };
        std::vector<VkDynamicState> dynamicStates;
        //--------------------
        graphicsPipelineCreateInfoPack() {
            SetCreateInfos();
            //�����������ߣ�createInfo.basePipelineIndex����Ϊ0������Ϊ-1
            createInfo.basePipelineIndex = -1;
        }
        //�ƶ�������������ָ�붼Ҫ���¸�ֵ
        graphicsPipelineCreateInfoPack(const graphicsPipelineCreateInfoPack& other) noexcept {
            createInfo = other.createInfo;
            SetCreateInfos();

            vertexInputStateCi = other.vertexInputStateCi;
            inputAssemblyStateCi = other.inputAssemblyStateCi;
            tessellationStateCi = other.tessellationStateCi;
            viewportStateCi = other.viewportStateCi;
            rasterizationStateCi = other.rasterizationStateCi;
            multisampleStateCi = other.multisampleStateCi;
            depthStencilStateCi = other.depthStencilStateCi;
            colorBlendStateCi = other.colorBlendStateCi;
            dynamicStateCi = other.dynamicStateCi;

            shaderStages = other.shaderStages;
            vertexInputBindings = other.vertexInputBindings;
            vertexInputAttributes = other.vertexInputAttributes;
            viewports = other.viewports;
            scissors = other.scissors;
            colorBlendAttachmentStates = other.colorBlendAttachmentStates;
            dynamicStates = other.dynamicStates;
            UpdateAllArrayAddresses();
        }
        //Getter��������û��const���η�
        operator VkGraphicsPipelineCreateInfo& () { return createInfo; }
        //Non-const Function
        //�ú������ڽ�����vector�����ݵĵ�ַ��ֵ������������Ϣ����Ӧ��Ա������Ӧ�ı����count
        void UpdateAllArrays() {
            createInfo.stageCount = shaderStages.size();
            vertexInputStateCi.vertexBindingDescriptionCount = vertexInputBindings.size();
            vertexInputStateCi.vertexAttributeDescriptionCount = vertexInputAttributes.size();
            viewportStateCi.viewportCount = viewports.size() ? uint32_t(viewports.size()) : dynamicViewportCount;
            viewportStateCi.scissorCount = scissors.size() ? uint32_t(scissors.size()) : dynamicScissorCount;
            colorBlendStateCi.attachmentCount = colorBlendAttachmentStates.size();
            dynamicStateCi.dynamicStateCount = dynamicStates.size();
            UpdateAllArrayAddresses();
        }
    private:
        //�ú������ڽ�������Ϣ�ĵ�ַ��ֵ��basePipelineIndex����Ӧ��Ա
        void SetCreateInfos() {
            createInfo.pVertexInputState = &vertexInputStateCi;
            createInfo.pInputAssemblyState = &inputAssemblyStateCi;
            createInfo.pTessellationState = &tessellationStateCi;
            createInfo.pViewportState = &viewportStateCi;
            createInfo.pRasterizationState = &rasterizationStateCi;
            createInfo.pMultisampleState = &multisampleStateCi;
            createInfo.pDepthStencilState = &depthStencilStateCi;
            createInfo.pColorBlendState = &colorBlendStateCi;
            createInfo.pDynamicState = &dynamicStateCi;
        }
        //�ú������ڽ�����vector�����ݵĵ�ַ��ֵ������������Ϣ����Ӧ��Ա�������ı����count
        void UpdateAllArrayAddresses() {
            createInfo.pStages = shaderStages.data();
            vertexInputStateCi.pVertexBindingDescriptions = vertexInputBindings.data();
            vertexInputStateCi.pVertexAttributeDescriptions = vertexInputAttributes.data();
            viewportStateCi.pViewports = viewports.data();
            viewportStateCi.pScissors = scissors.data();
            colorBlendStateCi.pAttachments = colorBlendAttachmentStates.data();
            dynamicStateCi.pDynamicStates = dynamicStates.data();
        }
    };


    class graphicsBasePlus {
        VkFormatProperties formatProperties[std::size(formatInfos_v1_0)] = {};
        commandPool commandPool_graphics;
        commandPool commandPool_presentation;
        commandPool commandPool_compute;
        commandBuffer commandBuffer_transfer;//��commandPool_graphics����
        commandBuffer commandBuffer_presentation;
        //��̬����
        static graphicsBasePlus singleton;
        //--------------------
        graphicsBasePlus() {
            //�ڴ����߼��豸ʱִ��Initialize()
            auto Initialize = [] {
                if (graphicsBase::Base().QueueFamilyIndex_Graphics() != VK_QUEUE_FAMILY_IGNORED)
                    singleton.commandPool_graphics.Create(graphicsBase::Base().QueueFamilyIndex_Graphics(), VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT),
                    singleton.commandPool_graphics.AllocateBuffers(singleton.commandBuffer_transfer);
                if (graphicsBase::Base().QueueFamilyIndex_Compute() != VK_QUEUE_FAMILY_IGNORED)
                    singleton.commandPool_compute.Create(graphicsBase::Base().QueueFamilyIndex_Compute(), VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
                if (graphicsBase::Base().QueueFamilyIndex_Presentation() != VK_QUEUE_FAMILY_IGNORED &&
                    graphicsBase::Base().QueueFamilyIndex_Presentation() != graphicsBase::Base().QueueFamilyIndex_Graphics() &&
                    graphicsBase::Base().SwapchainCreateInfo().imageSharingMode == VK_SHARING_MODE_EXCLUSIVE)
                    singleton.commandPool_presentation.Create(graphicsBase::Base().QueueFamilyIndex_Presentation(), VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT),
                    singleton.commandPool_presentation.AllocateBuffers(singleton.commandBuffer_presentation);
                /*���������*/
                };
            //�������߼��豸ʱִ��CleanUp()
            //����㲻��Ҫ���������豸��������������Vulkan�����漰�ؽ��߼��豸������ô��CleanUp�ص��Ǳ�Ҫ
            //�������н���ʱ�������Ƿ�������ص���graphicsBasePlus�еĶ���ػ�������graphicsBaseǰ��������
            auto CleanUp = [] {
                singleton.commandPool_graphics.~commandPool();
                singleton.commandPool_presentation.~commandPool();
                singleton.commandPool_compute.~commandPool();
                };
            graphicsBase::Plus(singleton);
            graphicsBase::Base().AddCallback_CreateDevice(Initialize);
            graphicsBase::Base().AddCallback_DestroyDevice(CleanUp);
        }
        graphicsBasePlus(graphicsBasePlus&&) = delete;
        ~graphicsBasePlus() = default;

    public:
        //Getter
        const commandPool& CommandPool_Graphics() const { return commandPool_graphics; }
        const commandPool& CommandPool_Compute() const { return commandPool_compute; }
        const commandBuffer& CommandBuffer_Transfer() const { return commandBuffer_transfer; }

        const VkFormatProperties & FormatProperties(VkFormat format) const {
#ifndef NDEBUG
            if (uint32_t(format) >= std::size(formatInfos_v1_0))
                outStream << std::format("[ FormatProperties ] ERROR\nThis function only supports definite formats provided by VK_VERSION_1_0.\n"),
                abort();
#endif
            return formatProperties[format];
        }

        //Const Function
    //�������ύ
        result_t ExecuteCommandBuffer_Graphics(VkCommandBuffer commandBuffer) const {
            fence fence;
            VkSubmitInfo submitInfo = {
                .commandBufferCount = 1,
                .pCommandBuffers = &commandBuffer
            };
            VkResult result = graphicsBase::Base().SubmitCommandBuffer_Graphics(submitInfo, fence);
            if (!result)
                fence.Wait();
            return result;
        }
        //�ú���ר��������ֶ����ύ���ڽ��ս�����ͼ��Ķ���������Ȩ���������
        result_t AcquireImageOwnership_Presentation(VkSemaphore semaphore_renderingIsOver, VkSemaphore semaphore_ownershipIsTransfered, VkFence fence = VK_NULL_HANDLE) const {
            if (VkResult result = commandBuffer_presentation.Begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT))
                return result;
            graphicsBase::Base().CmdTransferImageOwnership(commandBuffer_presentation);
            if (VkResult result = commandBuffer_presentation.End())
                return result;
            return graphicsBase::Base().SubmitCommandBuffer_Presentation(commandBuffer_presentation, semaphore_renderingIsOver, semaphore_ownershipIsTransfered, fence);
        }
    };
    inline graphicsBasePlus graphicsBasePlus::singleton;

    constexpr formatInfo FormatInfo(VkFormat format) {
#ifndef NDEBUG
        if (uint32_t(format) >= std::size(formatInfos_v1_0))
            outStream << std::format("[ FormatInfo ] ERROR\nThis function only supports definite formats provided by VK_VERSION_1_0.\n"),
            abort();
#endif
        return formatInfos_v1_0[uint32_t(format)];
    }
    constexpr VkFormat Corresponding16BitFloatFormat(VkFormat format_32BitFloat) {
        switch (format_32BitFloat) {
        case VK_FORMAT_R32_SFLOAT:
            return VK_FORMAT_R16_SFLOAT;
        case VK_FORMAT_R32G32_SFLOAT:
            return VK_FORMAT_R16G16_SFLOAT;
        case VK_FORMAT_R32G32B32_SFLOAT:
            return VK_FORMAT_R16G16B16_SFLOAT;
        case VK_FORMAT_R32G32B32A32_SFLOAT:
            return VK_FORMAT_R16G16B16A16_SFLOAT;
        }
        return format_32BitFloat;
    }
    inline const VkFormatProperties& FormatProperties(VkFormat format) {
        return graphicsBase::Plus().FormatProperties(format);
    }

    class stagingBuffer {
        static inline class {
            stagingBuffer* pointer = Create();
            stagingBuffer* Create() {
                static stagingBuffer stagingBuffer;
                graphicsBase::Base().AddCallback_DestroyDevice([] { stagingBuffer.~stagingBuffer(); });
                return &stagingBuffer;
            }
        public:
            stagingBuffer& Get() const { return *pointer; }
        } stagingBuffer_mainThread;

    protected:
        bufferMemory bufferMemory;
        VkDeviceSize memoryUsage = 0;//ÿ��ӳ����ڴ��С
        image aliasedImage;
    public:
        stagingBuffer() = default;
        stagingBuffer(VkDeviceSize size) {
            Expand(size);
        }
        //Getter
        operator VkBuffer() const { return bufferMemory.Buffer(); }
        const VkBuffer* Address() const { return bufferMemory.AddressOfBuffer(); }
        VkDeviceSize AllocationSize() const { return bufferMemory.AllocationSize(); }
        VkImage AliasedImage() const { return aliasedImage; }
        //Const Function
        //�ú������ڴӻ�����ȡ������
        void RetrieveData(void* pData_src, VkDeviceSize size) const {
            bufferMemory.RetrieveData(pData_src, size);
        }
        //Non-const Function
        //�ú����������������豸�ڴ��С����ʱ���·����ڴ�
        void Expand(VkDeviceSize size) {
            if (size <= AllocationSize())
                return;
            Release();
            VkBufferCreateInfo bufferCreateInfo = {
                .size = size,
                .usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT
            };
            bufferMemory.Create(bufferCreateInfo, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
        }
        //�ú��������ֶ��ͷ������ڴ沢�����豸�ڴ�ͻ�������handle
        void Release() {
            bufferMemory.~bufferMemory();
        }
        void* MapMemory(VkDeviceSize size) {
            Expand(size);
            void* pData_dst = nullptr;
            bufferMemory.MapMemory(pData_dst, size);
            memoryUsage = size;
            return pData_dst;
        }
        void UnmapMemory() {
            bufferMemory.UnmapMemory(memoryUsage);
            memoryUsage = 0;
        }
        //�ú��������򻺳���д������
        void BufferData(const void* pData_src, VkDeviceSize size) {
            Expand(size);
            bufferMemory.BufferData(pData_src, size);
        }
        //�ú����������Բ��ֵĻ��2dͼ��
        [[nodiscard]]
        VkImage AliasedImage2d(VkFormat format, VkExtent2D extent) {
            if (!(FormatProperties(format).linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT))
                return VK_NULL_HANDLE;
            VkDeviceSize imageDataSize = VkDeviceSize(FormatInfo(format).sizePerPixel) * extent.width * extent.height;
            if (imageDataSize > AllocationSize())
                return VK_NULL_HANDLE;
            VkImageFormatProperties imageFormatProperties = {};
            vkGetPhysicalDeviceImageFormatProperties(graphicsBase::Base().PhysicalDevice(),
                format, VK_IMAGE_TYPE_2D, VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_TRANSFER_SRC_BIT, 0, &imageFormatProperties);
        
            //�����������Ƿ�������Χ��
            if (extent.width > imageFormatProperties.maxExtent.width ||
                extent.height > imageFormatProperties.maxExtent.height ||
                imageDataSize > imageFormatProperties.maxResourceSize)
                return VK_NULL_HANDLE;//�粻����Ҫ�󣬷���VK_NULL_HANDLE

            VkImageCreateInfo imageCreateInfo = {
                .imageType = VK_IMAGE_TYPE_2D,
                .format = format,
                .extent = { extent.width, extent.height, 1 },
                .mipLevels = 1,
                .arrayLayers = 1,
                .samples = VK_SAMPLE_COUNT_1_BIT,
                .tiling = VK_IMAGE_TILING_LINEAR,
                .usage = VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
                .initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED
            };
            aliasedImage.~image();
            aliasedImage.Create(imageCreateInfo);

            VkImageSubresource subResource = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0 };
            VkSubresourceLayout subresourceLayout = {};
            vkGetImageSubresourceLayout(graphicsBase::Base().Device(), aliasedImage, &subResource, &subresourceLayout);
            if (subresourceLayout.size != imageDataSize)
                return VK_NULL_HANDLE;
            aliasedImage.BindMemory(bufferMemory.Memory());
            return aliasedImage;
        }

        //Static Function
        static VkBuffer Buffer_MainThread() {
            return stagingBuffer_mainThread.Get();
        }
        static void Expand_MainThread(VkDeviceSize size) {
            stagingBuffer_mainThread.Get().Expand(size);
        }
        static void Release_MainThread() {
            stagingBuffer_mainThread.Get().Release();
        }
        static void* MapMemory_MainThread(VkDeviceSize size) {
            return stagingBuffer_mainThread.Get().MapMemory(size);
        }
        static void UnmapMemory_MainThread() {
            stagingBuffer_mainThread.Get().UnmapMemory();
        }
        static void BufferData_MainThread(const void* pData_src, VkDeviceSize size) {
            stagingBuffer_mainThread.Get().BufferData(pData_src, size);
        }
        static void RetrieveData_MainThread(void* pData_src, VkDeviceSize size) {
            stagingBuffer_mainThread.Get().RetrieveData(pData_src, size);
        }
        [[nodiscard]]
        static VkImage AliasedImage2d_MainThread(VkFormat format, VkExtent2D extent) {
            return stagingBuffer_mainThread.Get().AliasedImage2d(format, extent);
        }
    };

    class deviceLocalBuffer {
    protected:
        bufferMemory bufferMemory;
    public:
        deviceLocalBuffer() = default;
        deviceLocalBuffer(VkDeviceSize size, VkBufferUsageFlags desiredUsages_Without_transfer_dst) {
            Create(size, desiredUsages_Without_transfer_dst);
        }
        //Getter
        operator VkBuffer() const { return bufferMemory.Buffer(); }
        const VkBuffer* Address() const { return bufferMemory.AddressOfBuffer(); }
        VkDeviceSize AllocationSize() const { return bufferMemory.AllocationSize(); }
        //Non-const Function
        void Create(VkDeviceSize size, VkBufferUsageFlags desiredUsages_Without_transfer_dst) {
            VkBufferCreateInfo bufferCreateInfo = {
                .size = size,
                .usage = desiredUsages_Without_transfer_dst | VK_BUFFER_USAGE_TRANSFER_DST_BIT
            };
            //��·ִ�У���һ�е�false||��Ϊ�˶���
            false ||
                bufferMemory.CreateBuffer(bufferCreateInfo) ||
                bufferMemory.AllocateMemory(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) && //&&��������ȼ�����||
                bufferMemory.AllocateMemory(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) ||
                bufferMemory.BindMemory();
        }
        void Recreate(VkDeviceSize size, VkBufferUsageFlags desiredUsages_Without_transfer_dst) {
            graphicsBase::Base().WaitIdle(); //deviceLocalBuffer��װ�Ļ��������ܻ���ÿһ֡�б�Ƶ��ʹ�ã��ؽ���֮ǰӦȷ�������豸û����ʹ����
            bufferMemory.~bufferMemory();
            Create(size, desiredUsages_Without_transfer_dst);
        }
        //Const Function
        void CmdUpdateBuffer(VkCommandBuffer commandBuffer, const void* pData_src, VkDeviceSize size_Limited_to_65536, VkDeviceSize offset = 0) const {
            vkCmdUpdateBuffer(commandBuffer, bufferMemory.Buffer(), offset, size_Limited_to_65536, pData_src);
        }
        //�����ڴӻ�������ͷ�������������ݿ飬���ݴ�С�Զ��ж�
        void CmdUpdateBuffer(VkCommandBuffer commandBuffer, const auto& data_src) const {
            vkCmdUpdateBuffer(commandBuffer, bufferMemory.Buffer(), 0, sizeof(data_src), &data_src);
        }

        //�����ڸ������������ݿ�
        void TransferData(const void* pData_src, VkDeviceSize size, VkDeviceSize offset = 0) const {
            if (bufferMemory.MemoryProperties() & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) {
                bufferMemory.BufferData(pData_src, size, offset);
                return;
            }
            stagingBuffer::BufferData_MainThread(pData_src, size);
            auto& commandBuffer = graphicsBase::Plus().CommandBuffer_Transfer();
            commandBuffer.Begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
            VkBufferCopy region = { 0, offset, size };
            vkCmdCopyBuffer(commandBuffer, stagingBuffer::Buffer_MainThread(), bufferMemory.Buffer(), 1, &region);
            commandBuffer.End();
            graphicsBase::Plus().ExecuteCommandBuffer_Graphics(commandBuffer);
        }
        //�����ڸ��²������Ķ�����ݣ�stride��ÿ�����ݼ�Ĳ���������offset��Ȼ��Ŀ�껺�����е�offset
        void TransferData(const void* pData_src, uint32_t elementCount, VkDeviceSize elementSize, VkDeviceSize stride_src, VkDeviceSize stride_dst, VkDeviceSize offset = 0) const {
            if (bufferMemory.MemoryProperties() & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) {
                void* pData_dst = nullptr;
                bufferMemory.MapMemory(pData_dst, stride_dst * elementCount, offset);
                for (size_t i = 0; i < elementCount; i++)
                    memcpy(stride_dst * i + static_cast<uint8_t*>(pData_dst), stride_src * i + static_cast<const uint8_t*>(pData_src), size_t(elementSize));
                bufferMemory.UnmapMemory(elementCount * stride_dst, offset);
                return;
            }
            stagingBuffer::BufferData_MainThread(pData_src, stride_src * elementCount);
            auto& commandBuffer = graphicsBase::Plus().CommandBuffer_Transfer();
            commandBuffer.Begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
            std::unique_ptr<VkBufferCopy[]> regions = std::make_unique<VkBufferCopy[]>(elementCount);
            for (size_t i = 0; i < elementCount; i++)
                regions[i] = { stride_src * i, stride_dst * i + offset, elementSize };
            vkCmdCopyBuffer(commandBuffer, stagingBuffer::Buffer_MainThread(), bufferMemory.Buffer(), elementCount, regions.get());
            commandBuffer.End();
            graphicsBase::Plus().ExecuteCommandBuffer_Graphics(commandBuffer);
        }
        //�����ڴӻ�������ͷ�������������ݿ飬���ݴ�С�Զ��ж�
        void TransferData(const auto& data_src) const {
            TransferData(&data_src, sizeof data_src);
        }
    };

    class vertexBuffer :public deviceLocalBuffer {
    public:
        vertexBuffer() = default;
        vertexBuffer(VkDeviceSize size, VkBufferUsageFlags otherUsages = 0) :deviceLocalBuffer(size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | otherUsages) {}
        //Non-const Function
        void Create(VkDeviceSize size, VkBufferUsageFlags otherUsages = 0) {
            deviceLocalBuffer::Create(size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | otherUsages);
        }
        void Recreate(VkDeviceSize size, VkBufferUsageFlags otherUsages = 0) {
            deviceLocalBuffer::Recreate(size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | otherUsages);
        }
    };

    class indexBuffer :public deviceLocalBuffer {
    public:
        indexBuffer() = default;
        indexBuffer(VkDeviceSize size, VkBufferUsageFlags otherUsages = 0) :deviceLocalBuffer(size, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | otherUsages) {}
        //Non-const Function
        void Create(VkDeviceSize size, VkBufferUsageFlags otherUsages = 0) {
            deviceLocalBuffer::Create(size, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | otherUsages);
        }
        void Recreate(VkDeviceSize size, VkBufferUsageFlags otherUsages = 0) {
            deviceLocalBuffer::Recreate(size, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | otherUsages);
        }
    };

    class uniformBuffer :public deviceLocalBuffer {
    public:
        uniformBuffer() = default;
        uniformBuffer(VkDeviceSize size, VkBufferUsageFlags otherUsages = 0) :deviceLocalBuffer(size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | otherUsages) {}
        //Non-const Function
        void Create(VkDeviceSize size, VkBufferUsageFlags otherUsages = 0) {
            deviceLocalBuffer::Create(size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | otherUsages);
        }
        void Recreate(VkDeviceSize size, VkBufferUsageFlags otherUsages = 0) {
            deviceLocalBuffer::Recreate(size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | otherUsages);
        }
        //Static Function
        static VkDeviceSize CalculateAlignedSize(VkDeviceSize dataSize) {
            const VkDeviceSize& alignment = graphicsBase::Base().PhysicalDeviceProperties().limits.minUniformBufferOffsetAlignment;
            return dataSize + alignment - 1 & ~(alignment - 1);
        }
    };

    class storageBuffer :public deviceLocalBuffer {
    public:
        storageBuffer() = default;
        storageBuffer(VkDeviceSize size, VkBufferUsageFlags otherUsages = 0) :deviceLocalBuffer(size, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | otherUsages) {}
        //Non-const Function
        void Create(VkDeviceSize size, VkBufferUsageFlags otherUsages = 0) {
            deviceLocalBuffer::Create(size, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | otherUsages);
        }
        void Recreate(VkDeviceSize size, VkBufferUsageFlags otherUsages = 0) {
            deviceLocalBuffer::Recreate(size, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | otherUsages);
        }
        //Static Function
        static VkDeviceSize CalculateAlignedSize(VkDeviceSize dataSize) {
            const VkDeviceSize& alignment = graphicsBase::Base().PhysicalDeviceProperties().limits.minStorageBufferOffsetAlignment;
            return dataSize + alignment - 1 & ~(alignment - 1);
        }
    };

    class texture {
    protected:
        static std::unique_ptr<uint8_t[]> LoadFile_Internal(
            const auto* address,             //�ַ���ָ�룬����Դ���ڴ��ַ
            size_t fileSize,                 //�ļ���С�����ҽ������������Դ���ڴ��ַʱ����Ҫ
            VkExtent2D& extent,              //ͼ���С������stb_image�ĺ���д��
            formatInfo requiredFormatInfo) { //�Զ�ȡ�������ݵĸ�ʽҪ��
#ifndef NDEBUG
            if (!(requiredFormatInfo.rawDataType == formatInfo::floatingPoint && requiredFormatInfo.sizePerComponent == 4) &&
                !(requiredFormatInfo.rawDataType == formatInfo::integer && Between_Closed<int32_t>(1, requiredFormatInfo.sizePerComponent, 2)))
                outStream << std::format("[ texture ] ERROR\nRequired format is not available for source image data!\n"),
                abort();
#endif
            int& width = reinterpret_cast<int&>(extent.width);
            int& height = reinterpret_cast<int&>(extent.height);
            int channelCount;
            void* pImageData = nullptr;
            if constexpr (std::same_as<decltype(address), const char*>) {
                if (requiredFormatInfo.rawDataType == formatInfo::integer)
                    if (requiredFormatInfo.sizePerComponent == 1)
                        pImageData = stbi_load(address, &width, &height, &channelCount, requiredFormatInfo.componentCount);
                    else
                        pImageData = stbi_load_16(address, &width, &height, &channelCount, requiredFormatInfo.componentCount);
                else
                    pImageData = stbi_loadf(address, &width, &height, &channelCount, requiredFormatInfo.componentCount);
                if (!pImageData)
                    outStream << std::format("[ texture ] ERROR\nFailed to load the file: {}\n", address);
            }
            if constexpr (std::same_as<decltype(address), const uint8_t*>) {
                if (fileSize > INT32_MAX) {
                    outStream << std::format("[ texture ] ERROR\nFailed to load image data from the given address! Data size must be less than 2G!\n");
                    return {};
                }
                if (requiredFormatInfo.rawDataType == formatInfo::integer)
                    if (requiredFormatInfo.sizePerComponent == 1)
                        pImageData = stbi_load_from_memory(address, fileSize, &width, &height, &channelCount, requiredFormatInfo.componentCount);
                    else
                        pImageData = stbi_load_16_from_memory(address, fileSize, &width, &height, &channelCount, requiredFormatInfo.componentCount);
                else
                    pImageData = stbi_loadf_from_memory(address, fileSize, &width, &height, &channelCount, requiredFormatInfo.componentCount);
                if (!pImageData)
                    outStream << std::format("[ texture ] ERROR\nFailed to load image data from the given address!\n");
            }
            return std::unique_ptr<uint8_t[]>(static_cast<uint8_t*>(pImageData));
        }

    public:
        [[nodiscard]]
        static std::unique_ptr<uint8_t[]> LoadFile(const char* filepath, VkExtent2D& extent, formatInfo requiredFormatInfo) {
            return LoadFile_Internal(filepath, 0, extent, requiredFormatInfo);
        }

        [[nodiscard]]
        static std::unique_ptr<uint8_t[]> LoadFile(const uint8_t* fileBinaries, size_t fileSize, VkExtent2D& extent, formatInfo requiredFormatInfo) {
            return LoadFile_Internal(fileBinaries, fileSize, extent, requiredFormatInfo);
        }

        std::pair<const uint8_t*, size_t> LoadResourceFromModule(int32_t resourceId, HMODULE hModule = NULL) {
            if (HRSRC hResource = FindResource(hModule, MAKEINTRESOURCE(resourceId), RT_RCDATA))
                if (HGLOBAL hData = LoadResource(hModule, hResource))
                    if (const uint8_t* pData = static_cast<uint8_t*>(LockResource(hData)))
                        return { pData, SizeofResource(hModule, hResource) };
            return {};
        }
    };


    struct imageOperation {
        struct imageMemoryBarrierParameterPack {
            const bool isNeeded = false;                            //�Ƿ���Ҫ���ϣ�Ĭ��Ϊfalse
            const VkPipelineStageFlags stage = 0;                   //srcStages��dstStages
            const VkAccessFlags access = 0;                         //srcAccessMask��dstAccessMask
            const VkImageLayout layout = VK_IMAGE_LAYOUT_UNDEFINED; //oldLayout��newLayout
            //Ĭ�Ϲ�������isNeeded����Ϊfalse
            constexpr imageMemoryBarrierParameterPack() = default;
            //��ָ�������������������뱻ȫ����ʾָ����isNeeded����ֵΪtrue
            constexpr imageMemoryBarrierParameterPack(VkPipelineStageFlags stage, VkAccessFlags access, VkImageLayout layout) :
                isNeeded(true), stage(stage), access(access), layout(layout) {}
        };
        static void CmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer buffer, VkImage image, const VkBufferImageCopy& region,
            imageMemoryBarrierParameterPack imb_from, imageMemoryBarrierParameterPack imb_to) {
            VkImageMemoryBarrier imageMemoryBarrier = {
                VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
                nullptr,
                imb_from.access,
                VK_ACCESS_TRANSFER_WRITE_BIT,
                imb_from.layout,
                VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                VK_QUEUE_FAMILY_IGNORED, //�޶���������Ȩת��
                VK_QUEUE_FAMILY_IGNORED,
                image,
                {
                    region.imageSubresource.aspectMask,
                    region.imageSubresource.mipLevel,
                    1,
                    region.imageSubresource.baseArrayLayer,
                    region.imageSubresource.layerCount 
                }
            };
            if (imb_from.isNeeded)
                vkCmdPipelineBarrier(commandBuffer, imb_from.stage, VK_PIPELINE_STAGE_TRANSFER_BIT, 0,
                    0, nullptr, 0, nullptr, 1, &imageMemoryBarrier);

            vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

            //����������Ҫ��������
            if (imb_to.isNeeded) {
                imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
                imageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
                imageMemoryBarrier.dstAccessMask = imb_to.access;
                imageMemoryBarrier.newLayout = imb_to.layout;
                vkCmdPipelineBarrier(commandBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, imb_to.stage, 0,
                    0, nullptr, 0, nullptr, 1, &imageMemoryBarrier);
            }
        }

        static void CmdBlitImage(VkCommandBuffer commandBuffer, VkImage image_src, VkImage image_dst, const VkImageBlit& region,
            imageMemoryBarrierParameterPack imb_dst_from, imageMemoryBarrierParameterPack imb_dst_to, VkFilter filter = VK_FILTER_LINEAR) {
            VkImageMemoryBarrier imageMemoryBarrier = {
                VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
                nullptr,
                imb_dst_from.access,
                VK_ACCESS_TRANSFER_WRITE_BIT,
                imb_dst_from.layout,
                VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                VK_QUEUE_FAMILY_IGNORED,
                VK_QUEUE_FAMILY_IGNORED,
                image_dst,
                {
                    region.dstSubresource.aspectMask,
                    region.dstSubresource.mipLevel,
                    1,
                    region.dstSubresource.baseArrayLayer,
                    region.dstSubresource.layerCount 
                }
            };
            if (imb_dst_from.isNeeded)
                vkCmdPipelineBarrier(commandBuffer, imb_dst_from.stage, VK_PIPELINE_STAGE_TRANSFER_BIT, 0,
                    0, nullptr, 0, nullptr, 1, &imageMemoryBarrier);
            vkCmdBlitImage(commandBuffer,
                image_src, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                image_dst, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                1, &region, filter);
            if (imb_dst_to.isNeeded) {
                imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
                imageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
                imageMemoryBarrier.dstAccessMask = imb_dst_to.access;
                imageMemoryBarrier.newLayout = imb_dst_to.layout;
                vkCmdPipelineBarrier(commandBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, imb_dst_to.stage, 0,
                    0, nullptr, 0, nullptr, 1, &imageMemoryBarrier);
            }
        }
    };

}