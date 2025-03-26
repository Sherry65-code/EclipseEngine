#pragma once

#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>
#include <volk.h>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <optional>
#include <set>
#include <array>
#include <chrono>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class evk {
private:
	VkInstance instance{};
	VkDebugUtilsMessengerEXT debugMessenger{};
	VkPhysicalDevice physicalDevice{};
	VkDevice device{};
	VkQueue graphicsQueue{};
	VkQueue presentQueue{};
	VkSurfaceKHR surface{};
	VkSwapchainKHR swapchain{};
	std::vector<VkImage> swapchainImages{};
	VkFormat swapchainImageFormat{};
	VkExtent2D swapchainExtent{};
	std::vector<VkImageView> swapchainImageViews{};
	VkPipelineLayout pipelineLayout{};
	VkRenderPass renderPass{};
	VkPipeline graphicsPipeline{};
	std::vector<VkFramebuffer> swapchainFrameBuffers{};
	VkCommandPool commandPool{};
	std::vector<VkCommandBuffer> commandBuffers{};
	std::vector<VkSemaphore> imageAvailableSemaphores{};
	std::vector<VkSemaphore> renderFinishedSemaphores{};
	std::vector<VkFence> inFlightFences{};
	bool framebufferResized{};
	VkDescriptorSetLayout descriptorSetLayout{};

	VkBuffer vertexBuffer{};
	VkBuffer indexBuffer{};
	std::vector<VkBuffer> uniformBuffers{};

	std::vector<void*> uniformBuffersMapped{};

	VkDescriptorPool descriptorPool{};
	std::vector<VkDescriptorSet> descriptorSets{};

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily; // Presentation support bro, its not present family MF :)

		bool isComplete() const {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};
	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};
	struct UniformBufferObject {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
	};

	bool checkValidationLayerSupport();
	std::vector<const char*> getRequiredExtensions();
	VkPhysicalDevice chooseBestDevice(std::vector<VkPhysicalDevice>& devices);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) const;
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) const;
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	VkShaderModule createShaderModule(const std::vector<char>& code) const;
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) const;
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	void updateUniformBuffer(uint32_t currentImage);

public:
	void passWindowPointer(void* window);
	void recreateSwapChain();
	void cleanupSwapChain();
	void updateFramebuffer();

	void initalizeDriver();
	void initializeVulkanMemoryAllocator();

	void createInstance();
	void setupDebugMessenger();
	void createSurface();
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createSwapChain();
	void createImageViews();
	void createRenderPass();
	void createDescriptiorSetLayout();
	void createGraphicsPipeline();
	void createFramebuffers();
	void createCommandPool();
	void createVertexBuffer();
	void createIndexBuffer();
	void createUniformBuffers();
	void createDescriptorPool();
	void createDescriptorSets();
	void createCommandBuffer();
	void createSyncObjects();

	void drawFrame();

	~evk();
};