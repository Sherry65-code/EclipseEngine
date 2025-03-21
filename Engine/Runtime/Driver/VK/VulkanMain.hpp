#pragma once

#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>
#include <Volk/volk.h>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <optional>

class evk {
private:
	VkInstance instance{};
	VkDebugUtilsMessengerEXT debugMessenger{};
	VkPhysicalDevice physicalDevice{};
	VkDevice device{};
	VkQueue graphicsQueue{};

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;

		bool isComplete() const {
			return graphicsFamily.has_value();
		}
	};

	bool checkValidationLayerSupport();
	std::vector<const char*> getRequiredExtensions();
	void setupDebugMessenger();
	VkPhysicalDevice chooseBestDevice(std::vector<VkPhysicalDevice>& devices);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
public:
	void createInstance();
	void pickPhysicalDevice();
	void createLogicalDevice();

	~evk();
};