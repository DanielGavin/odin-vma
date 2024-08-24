### odin-vma

Binding for VulkanMemoryAllocator.

## Usage

The blob for the Windows library is shipped with the repository, but not for Linux. All code is modified to import the required files if you are on Linux, so no changes to the code need to be made. [Build instructions for VMA on linux](##building-vma)

```
vulkan_functions := vma.create_vulkan_functions();

create_info := vma.AllocatorCreateInfo {
	vulkanApiVersion = vulkan.API_VERSION_1_2,
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

## Building VMA
The library needs to be built with dynamically linked and statically linked functions off - we are passing the pointers to VMA manually.

```
option(VMA_STATIC_VULKAN_FUNCTIONS "Link statically with Vulkan API" OFF)
option(VMA_DYNAMIC_VULKAN_FUNCTIONS "Fetch pointers to Vulkan functions internally (no static linking)" OFF)
```

Linux build instructions with the above flags set to OFF, starting in the root of the repo:
```
git submodule update --init --recursive
cd VulkanMemoryAllocator
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DVMA_STATIC_VULKAN_FUNCTIONS=OFF -DVMA_DYNAMIC_VULKAN_FUNCTIONS=OFF
cd build
make
cd ../../
cp VulkanMemoryAllocator/build/src/libVulkanMemoryAllocator.a external/
```
