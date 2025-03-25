#include "VulkanMain.hpp"

#include <GLFW/glfw3.h>
#include <Runtime/Standard/IO.hpp>

#ifndef NDEBUG
constexpr bool enableValidationLayers = true;
#else
constexpr bool enableValidationLayers = false;
#endif

const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};
const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

GLFWwindow* pWindow{};



// HELPERS






static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
	if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
		io::logMessage(io::LogLevel::ERROR, "{}", pCallbackData->pMessage);
	}
	else {
		io::logMessage(io::LogLevel::DEBUG, "{}", pCallbackData->pMessage);
	}
	return VK_FALSE;
}

bool evk::checkValidationLayerSupport() {
	uint32_t layer_count{};
	vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

	std::vector<VkLayerProperties> available_layers(layer_count);
	vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

	for (const char* layer_name : validationLayers) {
		bool layer_found = false;

		for (const auto& layer_properties : available_layers) {
			if (strcmp(layer_name, layer_properties.layerName) == 0) {
				layer_found = true;
				break;
			}
		}

		if (!layer_found) {
			return false;
		}
	}

	return true;
}

std::vector<const char*> evk::getRequiredExtensions() {
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions{};
	
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (enableValidationLayers) {
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return extensions;
}

VkPhysicalDevice evk::chooseBestDevice(std::vector<VkPhysicalDevice>& devices) {
	
	uint32_t i = 0;
	uint32_t deviceIndex{};
	uint64_t maxScore{};

	for (VkPhysicalDevice& current_device : devices) {
		
		VkPhysicalDeviceProperties properties{};
		vkGetPhysicalDeviceProperties(current_device, &properties);
		VkPhysicalDeviceFeatures features{};
		vkGetPhysicalDeviceFeatures(current_device, &features);
		QueueFamilyIndices qfi{};
		SwapChainSupportDetails scsd{};

		qfi = findQueueFamilies(current_device);
		scsd = querySwapChainSupport(current_device);

		uint64_t score{};

		if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) score += 1000;
		score += properties.limits.maxImageDimension2D;
		if (!features.geometryShader) score = 0;
		if (!qfi.graphicsFamily.has_value()) score = 0;
		if (!checkDeviceExtensionSupport(current_device)) score = 0;
		if (scsd.formats.empty() && scsd.presentModes.empty()) score = 0;


		if (score > maxScore) {
			maxScore = score;
			deviceIndex = i;
		}

		i++;
	
	}

	if (maxScore == 0) throw std::exception("Failed to find a GPU with required features!");

	return devices[deviceIndex];

}

evk::QueueFamilyIndices evk::findQueueFamilies(VkPhysicalDevice device) const {
	QueueFamilyIndices indices{};

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies) {
		// Check for graphics queue support
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}
		
		// Check for presentation queue support
		VkBool32 presentSupport{};
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
		if (presentSupport) {
			indices.presentFamily = i;
		}

		if (indices.isComplete()) break;
		i++;
	}

	return indices;
}

bool evk::checkDeviceExtensionSupport(VkPhysicalDevice device) {
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

	for (const auto& extension : availableExtensions) {
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}

evk::SwapChainSupportDetails evk::querySwapChainSupport(VkPhysicalDevice device) const {
	SwapChainSupportDetails details;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);
	
	uint32_t formatCount{};
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

	if (formatCount != 0) {
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
	}

	uint32_t presentModeCount{};
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

	if (presentModeCount != 0) {
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
	}

	return details;
}

VkSurfaceFormatKHR evk::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
	for (const auto& availableFormat : availableFormats) {
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return availableFormat;
		}
	}

	return availableFormats[0];
}

VkPresentModeKHR evk::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
	for (const auto& availablePresentMode : availablePresentModes) {
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			return availablePresentMode;
		}
	}

	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D evk::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		return capabilities.currentExtent;
	}
	else {
		int width{};
		int height{};
		glfwGetFramebufferSize(pWindow, &width, &height);

		VkExtent2D actualExtent = {
			static_cast<uint32_t>(width),
			static_cast<uint32_t>(height)
		};

		actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

		return actualExtent;
	}
}

// VULKAN_MAIN





void evk::passWindowPointer(void* window) {
	pWindow = (GLFWwindow*)window;
}

void evk::createInstance() {
	if (volkInitialize() != VK_SUCCESS) throw std::exception("Failed to link vulkan driver to application!");

	if (enableValidationLayers && !checkValidationLayerSupport()) throw std::exception("Failed to find validation layers!");

	VkApplicationInfo applicationInfo{};
	applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	applicationInfo.pApplicationName = "Eclipse Studios";
	applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.pEngineName = "Eclipse Engine";
	applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.apiVersion = volkGetInstanceVersion();

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &applicationInfo;

	auto extensions = getRequiredExtensions();
	createInfo.enabledExtensionCount = extensions.size();
	createInfo.ppEnabledExtensionNames = extensions.data();

	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) throw std::exception("Failed to create vulkan instance!");

	volkLoadInstance(instance);

	setupDebugMessenger();
}

void evk::setupDebugMessenger() {
	if (!enableValidationLayers) return;

	VkDebugUtilsMessengerCreateInfoEXT createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = debugCallback;
	createInfo.pUserData = nullptr;

	if (vkCreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) throw std::exception("Failed to create debug messenger!");
}

void evk::createSurface() {
	if (!pWindow) throw std::exception("Window pointer not passed to driver!");
	if (glfwCreateWindowSurface(instance, pWindow, nullptr, &surface) != VK_SUCCESS) 
		throw std::exception("Failed to create window surface!");
}

void evk::pickPhysicalDevice() {
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	if (!deviceCount) {
		throw std::exception("Failed to find device with Vulkan Support!");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	physicalDevice = chooseBestDevice(devices);

	VkPhysicalDeviceProperties properties{};
	vkGetPhysicalDeviceProperties(physicalDevice, &properties);

	io::logMessage(io::LogLevel::INFO, "Device Selected : {}", properties.deviceName);
	io::logMessage(io::LogLevel::INFO, "Vulkan Version  : {}", properties.driverVersion);
}

void evk::createLogicalDevice() {
	QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
	
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

	float queuePriority = 1.0f;
	for (uint32_t queueFamily : uniqueQueueFamilies) {
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	VkPhysicalDeviceFeatures deviceFeatures{};
	vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pEnabledFeatures = &deviceFeatures;

	createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = deviceExtensions.data();

	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) throw std::exception("Failed to create logical device!");

	vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
	vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
}

void evk::createSwapChain() {
	SwapChainSupportDetails swapchainSupport = querySwapChainSupport(physicalDevice);

	VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapchainSupport.formats);
	VkPresentModeKHR presentMode = chooseSwapPresentMode(swapchainSupport.presentModes);
	VkExtent2D extent = chooseSwapExtent(swapchainSupport.capabilities);

	uint32_t imageCount{};
	if (swapchainSupport.capabilities.maxImageCount == 0) {
		imageCount = swapchainSupport.capabilities.minImageCount + 1;
	}
	else {
		imageCount = std::clamp(swapchainSupport.capabilities.minImageCount + 1, swapchainSupport.capabilities.minImageCount, swapchainSupport.capabilities.maxImageCount);
	}

	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = surface;
	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
	uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

	if (indices.graphicsFamily.value() != indices.presentFamily.value()) {
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else {
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0;
		createInfo.pQueueFamilyIndices = nullptr;
	}

	createInfo.preTransform = swapchainSupport.capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapchain) != VK_SUCCESS) throw std::exception("Failed to create swap chain!");

	vkGetSwapchainImagesKHR(device, swapchain, &imageCount, nullptr);
	swapchainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(device, swapchain, &imageCount, swapchainImages.data());

	swapchainImageFormat = surfaceFormat.format;
	swapchainExtent = extent;

}

void evk::createImageViews() {
	swapchainImageViews.resize(swapchainImages.size());

	for (size_t i = 0; i < swapchainImages.size(); i++) {
		VkImageViewCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = swapchainImages[i];
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = swapchainImageFormat;
		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;

		if (vkCreateImageView(device, &createInfo, nullptr, &swapchainImageViews[i]) != VK_SUCCESS) {
			throw std::exception("Failed to create image views");
		}
		
	}
}

void evk::createGraphicsPipeline() {

}

// DESTRUCTOR








evk::~evk() {
	for (auto imageView : swapchainImageViews) {
		vkDestroyImageView(device, imageView, nullptr);
	}
	if (swapchain) vkDestroySwapchainKHR(device, swapchain, nullptr);
	if (device) {
		vkDeviceWaitIdle(device);
		vkDestroyDevice(device, nullptr);
	}
	if (surface) vkDestroySurfaceKHR(instance, surface, nullptr);
	if (debugMessenger) vkDestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
	if (instance) vkDestroyInstance(instance, nullptr);
}