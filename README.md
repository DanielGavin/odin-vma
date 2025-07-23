### odin-vma

Binding for VulkanMemoryAllocator.

## Usage

The blob for the Windows library is shipped with the repository, but not for Linux. All code is modified to import the required files if you are on Linux, so no changes to the code need to be made. [Build instructions for VMA on linux](## Building VMA for Linux)

```
vulkan_functions := vma.create_vulkan_functions();

create_info := vma.AllocatorCreateInfo {
	vulkanApiVersion = vulkan.API_VERSION_1_3,
	physicalDevice = physical_device,
	device = device,
	instance = instance,
	pVulkanFunctions = &vulkan_functions,
};

if vma.CreateAllocator(&create_info, &allocator) != .SUCCESS {
	log.error("Failed to CreateAllocator");
}

```

## Introduction to VMA
https://gpuopen-librariesandsdks.github.io/VulkanMemoryAllocator/html/quick_start.html#quick_start_initialization

## Building VMA for Linux
The library needs to be built with dynamically linked and statically linked functions off - we are passing the pointers to VMA manually. Fortunately, the build script should already take care of this for vma version 3.2.1.

Example for building for vulkan 1.3:
```
./build.sh 3
```
