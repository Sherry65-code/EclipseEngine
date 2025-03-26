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

	bool checkValidationLayerSupport();
	std::vector<const char*> getRequiredExtensions();
	VkPhysicalDevice chooseBestDevice(std::vector<VkPhysicalDevice>& devices);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) const;
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) const;
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	VkShaderModule createShaderModule(const std::vector<char>& code);
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

public:
	void passWindowPointer(void* window);
	void recreateSwapChain();
	void cleanupSwapChain();
	void updateFramebuffer();

	void initalizeDriver();
	
	void createInstance();
	void setupDebugMessenger();
	void createSurface();
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createSwapChain();
	void createImageViews();
	void createRenderPass();
	void createGraphicsPipeline();
	void createFramebuffers();
	void createCommandPool();
	void createCommandBuffer();
	void createSyncObjects();

	void drawFrame();

	~evk();
};