### odin-vma

Binding for VulkanMemoryAllocator.

## Usage

```
vulkan_functions := vma.create_vulkan_functions();

create_info := vma.AllocatorCreateInfo {
	vulkanApiVersion = vulkan.API_VERSION_1_2,
	physicalDevice = device.physical_device,
	device = device.logical_device,
	instance = render_context.instance,
	pVulkanFunctions = &vulkan_functions,
};

if vma.CreateAllocator(&create_info, &device.allocator) != .SUCCESS {
	log.error("Failed to CreateAllocator");
}

```

## Introduction to vma
https://gpuopen-librariesandsdks.github.io/VulkanMemoryAllocator/html/quick_start.html#quick_start_initialization