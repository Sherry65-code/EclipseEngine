#include "VulkanMain.hpp"

#include <GLFW/glfw3.h>
#include <Runtime/Standard/IO.hpp>

#ifndef NDEBUG
constexpr bool enable_validation_layers = true;
#else
constexpr bool enable_validation_layers = false;
#endif

const std::vector<const char*> validation_layers = {
	"VK_LAYER_KHRONOS_validation"
};






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

	for (const char* layer_name : validation_layers) {
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

	if (enable_validation_layers) {
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return extensions;
}

void evk::setupDebugMessenger() {
	if (!enable_validation_layers) return;

	VkDebugUtilsMessengerCreateInfoEXT createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = debugCallback;
	createInfo.pUserData = nullptr;

	if (vkCreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) throw std::exception("Failed to create debug messenger!");
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
		qfi = findQueueFamilies(current_device);

		uint64_t score{};

		if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) score += 1000;
		score += properties.limits.maxImageDimension2D;
		if (!features.geometryShader) score = 0;
		if (!qfi.graphicsFamily.has_value()) score = 0;

		if (score > maxScore) {
			maxScore = score;
			deviceIndex = i;
		}

		i++;
	
	}

	if (maxScore == 0) throw std::exception("Failed to find a GPU with required features!");

	return devices[deviceIndex];

}

evk::QueueFamilyIndices evk::findQueueFamilies(VkPhysicalDevice device) {
	QueueFamilyIndices indices{};

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}
		if (indices.isComplete()) break;
		i++;
	}

	return indices;
}


// VULKAN_MAIN







void evk::createInstance() {
	if (volkInitialize() != VK_SUCCESS) throw std::exception("Failed to link vulkan driver to application!");

	if (enable_validation_layers && !checkValidationLayerSupport()) throw std::exception("Failed to find validation layers!");

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

	if (enable_validation_layers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
		createInfo.ppEnabledLayerNames = validation_layers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) throw std::exception("Failed to create vulkan instance!");

	volkLoadInstance(instance);

	setupDebugMessenger();
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

	VkDeviceQueueCreateInfo queueCreateInfo{};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
	queueCreateInfo.queueCount = 1;

	float queuePriority = 1.0f;
	queueCreateInfo.pQueuePriorities = &queuePriority;

	VkPhysicalDeviceFeatures deviceFeatures{};
	vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.queueCreateInfoCount = 1;
	createInfo.pEnabledFeatures = &deviceFeatures;

	createInfo.enabledExtensionCount = 0;

	if (enable_validation_layers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
		createInfo.ppEnabledLayerNames = validation_layers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) throw std::exception("Failed to create logical device!");

	vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
}

// DESTRUCTOR








evk::~evk() {
	if (device) {
		vkDeviceWaitIdle(device);
		vkDestroyDevice(device, nullptr);
	}
	if (debugMessenger) vkDestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
	if (instance) vkDestroyInstance(instance, nullptr);
}