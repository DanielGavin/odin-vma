//
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef AMD_VULKAN_MEMORY_ALLOCATOR_H
#define AMD_VULKAN_MEMORY_ALLOCATOR_H

/** \mainpage Vulkan Memory Allocator

<b>Version 3.0.0-development</b> (2021-06-21)

Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved. \n
License: MIT

Documentation of all members: vk_mem_alloc.h

\section main_table_of_contents Table of contents

- <b>User guide</b>
  - \subpage quick_start
    - [Project setup](@ref quick_start_project_setup)
    - [Initialization](@ref quick_start_initialization)
    - [Resource allocation](@ref quick_start_resource_allocation)
  - \subpage choosing_memory_type
    - [Usage](@ref choosing_memory_type_usage)
    - [Required and preferred flags](@ref choosing_memory_type_required_preferred_flags)
    - [Explicit memory types](@ref choosing_memory_type_explicit_memory_types)
    - [Custom memory pools](@ref choosing_memory_type_custom_memory_pools)
    - [Dedicated allocations](@ref choosing_memory_type_dedicated_allocations)
  - \subpage memory_mapping
    - [Mapping functions](@ref memory_mapping_mapping_functions)
    - [Persistently mapped memory](@ref memory_mapping_persistently_mapped_memory)
    - [Cache flush and invalidate](@ref memory_mapping_cache_control)
    - [Finding out if memory is mappable](@ref memory_mapping_finding_if_memory_mappable)
  - \subpage staying_within_budget
    - [Querying for budget](@ref staying_within_budget_querying_for_budget)
    - [Controlling memory usage](@ref staying_within_budget_controlling_memory_usage)
  - \subpage resource_aliasing
  - \subpage custom_memory_pools
    - [Choosing memory type index](@ref custom_memory_pools_MemTypeIndex)
    - [Linear allocation algorithm](@ref linear_algorithm)
      - [Free-at-once](@ref linear_algorithm_free_at_once)
      - [Stack](@ref linear_algorithm_stack)
      - [Double stack](@ref linear_algorithm_double_stack)
      - [Ring buffer](@ref linear_algorithm_ring_buffer)
    - [Buddy allocation algorithm](@ref buddy_algorithm)
  - \subpage defragmentation
      - [Defragmenting CPU memory](@ref defragmentation_cpu)
      - [Defragmenting GPU memory](@ref defragmentation_gpu)
      - [Additional notes](@ref defragmentation_additional_notes)
      - [Writing custom allocation algorithm](@ref defragmentation_custom_algorithm)
  - \subpage lost_allocations
  - \subpage statistics
    - [Numeric statistics](@ref statistics_numeric_statistics)
    - [JSON dump](@ref statistics_json_dump)
  - \subpage allocation_annotation
    - [Allocation user data](@ref allocation_user_data)
    - [Allocation names](@ref allocation_names)
  - \subpage debugging_memory_usage
    - [Memory initialization](@ref debugging_memory_usage_initialization)
    - [Margins](@ref debugging_memory_usage_margins)
    - [Corruption detection](@ref debugging_memory_usage_corruption_detection)
  - \subpage record_and_replay
  - \subpage opengl_interop
- \subpage usage_patterns
  - [Common mistakes](@ref usage_patterns_common_mistakes)
  - [Simple patterns](@ref usage_patterns_simple)
  - [Advanced patterns](@ref usage_patterns_advanced)
- \subpage configuration
  - [Pointers to Vulkan functions](@ref config_Vulkan_functions)
  - [Custom host memory allocator](@ref custom_memory_allocator)
  - [Device memory allocation callbacks](@ref allocation_callbacks)
  - [Device heap memory limit](@ref heap_memory_limit)
  - \subpage vk_khr_dedicated_allocation
  - \subpage enabling_buffer_device_address
  - \subpage vk_amd_device_coherent_memory
- \subpage general_considerations
  - [Thread safety](@ref general_considerations_thread_safety)
  - [Validation layer warnings](@ref general_considerations_validation_layer_warnings)
  - [Allocation algorithm](@ref general_considerations_allocation_algorithm)
  - [Features not supported](@ref general_considerations_features_not_supported)

\section main_see_also See also

- [Product page on GPUOpen](https://gpuopen.com/gaming-product/vulkan-memory-allocator/)
- [Source repository on GitHub](https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator)
*/

#ifdef __cplusplus
extern "C" {
#endif

/*
Define this macro to 0/1 to disable/enable support for recording functionality,
available through VmaAllocatorCreateInfo::pRecordSettings.
*/
#ifndef VMA_RECORDING_ENABLED
    #define VMA_RECORDING_ENABLED 0
#endif

#if defined(__ANDROID__) && defined(VK_NO_PROTOTYPES) && VMA_STATIC_VULKAN_FUNCTIONS
    extern PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    extern PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr;
    extern PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties;
    extern PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties;
    extern PFN_vkAllocateMemory vkAllocateMemory;
    extern PFN_vkFreeMemory vkFreeMemory;
    extern PFN_vkMapMemory vkMapMemory;
    extern PFN_vkUnmapMemory vkUnmapMemory;
    extern PFN_vkFlushMappedMemoryRanges vkFlushMappedMemoryRanges;
    extern PFN_vkInvalidateMappedMemoryRanges vkInvalidateMappedMemoryRanges;
    extern PFN_vkBindBufferMemory vkBindBufferMemory;
    extern PFN_vkBindImageMemory vkBindImageMemory;
    extern PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements;
    extern PFN_vkGetImageMemoryRequirements vkGetImageMemoryRequirements;
    extern PFN_vkCreateBuffer vkCreateBuffer;
    extern PFN_vkDestroyBuffer vkDestroyBuffer;
    extern PFN_vkCreateImage vkCreateImage;
    extern PFN_vkDestroyImage vkDestroyImage;
    extern PFN_vkCmdCopyBuffer vkCmdCopyBuffer;
    #if VMA_VULKAN_VERSION >= 1001000
        extern PFN_vkGetBufferMemoryRequirements2 vkGetBufferMemoryRequirements2;
        extern PFN_vkGetImageMemoryRequirements2 vkGetImageMemoryRequirements2;
        extern PFN_vkBindBufferMemory2 vkBindBufferMemory2;
        extern PFN_vkBindImageMemory2 vkBindImageMemory2;
        extern PFN_vkGetPhysicalDeviceMemoryProperties2 vkGetPhysicalDeviceMemoryProperties2;
    #endif // #if VMA_VULKAN_VERSION >= 1001000
#endif // #if defined(__ANDROID__) && VMA_STATIC_VULKAN_FUNCTIONS && VK_NO_PROTOTYPES

#ifndef VULKAN_H_
    #include <vulkan/vulkan.h>
#endif

// Define this macro to declare maximum supported Vulkan version in format AAABBBCCC,
// where AAA = major, BBB = minor, CCC = patch.
// If you want to use version > 1.0, it still needs to be enabled via VmaAllocatorCreateInfo::vulkanApiVersion.
#if !defined(VMA_VULKAN_VERSION)
    #if defined(VK_VERSION_1_2)
        #define VMA_VULKAN_VERSION 1002000
    #elif defined(VK_VERSION_1_1)
        #define VMA_VULKAN_VERSION 1001000
    #else
        #define VMA_VULKAN_VERSION 1000000
    #endif
#endif

#if !defined(VMA_DEDICATED_ALLOCATION)
    #if VK_KHR_get_memory_requirements2 && VK_KHR_dedicated_allocation
        #define VMA_DEDICATED_ALLOCATION 1
    #else
        #define VMA_DEDICATED_ALLOCATION 0
    #endif
#endif

#if !defined(VMA_BIND_MEMORY2)
    #if VK_KHR_bind_memory2
        #define VMA_BIND_MEMORY2 1
    #else
        #define VMA_BIND_MEMORY2 0
    #endif
#endif

#if !defined(VMA_MEMORY_BUDGET)
    #if VK_EXT_memory_budget && (VK_KHR_get_physical_device_properties2 || VMA_VULKAN_VERSION >= 1001000)
        #define VMA_MEMORY_BUDGET 1
    #else
        #define VMA_MEMORY_BUDGET 0
    #endif
#endif

// Defined to 1 when VK_KHR_buffer_device_address device extension or equivalent core Vulkan 1.2 feature is defined in its headers.
#if !defined(VMA_BUFFER_DEVICE_ADDRESS)
    #if VK_KHR_buffer_device_address || VMA_VULKAN_VERSION >= 1002000
        #define VMA_BUFFER_DEVICE_ADDRESS 1
    #else
        #define VMA_BUFFER_DEVICE_ADDRESS 0
    #endif
#endif

// Defined to 1 when VK_EXT_memory_priority device extension is defined in Vulkan headers.
#if !defined(VMA_MEMORY_PRIORITY)
    #if VK_EXT_memory_priority
        #define VMA_MEMORY_PRIORITY 1
    #else
        #define VMA_MEMORY_PRIORITY 0
    #endif
#endif

// Defined to 1 when VK_KHR_external_memory device extension is defined in Vulkan headers.
#if !defined(VMA_EXTERNAL_MEMORY)
    #if VK_KHR_external_memory
        #define VMA_EXTERNAL_MEMORY 1
    #else
        #define VMA_EXTERNAL_MEMORY 0
    #endif
#endif

// Define these macros to decorate all public functions with additional code,
// before and after returned type, appropriately. This may be useful for
// exporting the functions when compiling VMA as a separate library. Example:
// #define VMA_CALL_PRE  __declspec(dllexport)
// #define VMA_CALL_POST __cdecl
#ifndef VMA_CALL_PRE
    #define VMA_CALL_PRE
#endif
#ifndef VMA_CALL_POST
    #define VMA_CALL_POST
#endif

// Define this macro to decorate pointers with an attribute specifying the
// length of the array they point to if they are not null.
//
// The length may be one of
// - The name of another parameter in the argument list where the pointer is declared
// - The name of another member in the struct where the pointer is declared
// - The name of a member of a struct type, meaning the value of that member in
//   the context of the call. For example
//   VMA_LEN_IF_NOT_NULL("VkPhysicalDeviceMemoryProperties::memoryHeapCount"),
//   this means the number of memory heaps available in the device associated
//   with the VmaAllocator being dealt with.
#ifndef VMA_LEN_IF_NOT_NULL
    #define VMA_LEN_IF_NOT_NULL(len)
#endif

// The VMA_NULLABLE macro is defined to be _Nullable when compiling with Clang.
// see: https://clang.llvm.org/docs/AttributeReference.html#nullable
#ifndef VMA_NULLABLE
    #ifdef __clang__
        #define VMA_NULLABLE _Nullable
    #else
        #define VMA_NULLABLE
    #endif
#endif

// The VMA_NOT_NULL macro is defined to be _Nonnull when compiling with Clang.
// see: https://clang.llvm.org/docs/AttributeReference.html#nonnull
#ifndef VMA_NOT_NULL
    #ifdef __clang__
        #define VMA_NOT_NULL _Nonnull
    #else
        #define VMA_NOT_NULL
    #endif
#endif

// If non-dispatchable handles are represented as pointers then we can give
// then nullability annotations
#ifndef VMA_NOT_NULL_NON_DISPATCHABLE
    #if defined(__LP64__) || defined(_WIN64) || (defined(__x86_64__) && !defined(__ILP32__) ) || defined(_M_X64) || defined(__ia64) || defined (_M_IA64) || defined(__aarch64__) || defined(__powerpc64__)
        #define VMA_NOT_NULL_NON_DISPATCHABLE VMA_NOT_NULL
    #else
        #define VMA_NOT_NULL_NON_DISPATCHABLE
    #endif
#endif

#ifndef VMA_NULLABLE_NON_DISPATCHABLE
    #if defined(__LP64__) || defined(_WIN64) || (defined(__x86_64__) && !defined(__ILP32__) ) || defined(_M_X64) || defined(__ia64) || defined (_M_IA64) || defined(__aarch64__) || defined(__powerpc64__)
        #define VMA_NULLABLE_NON_DISPATCHABLE VMA_NULLABLE
    #else
        #define VMA_NULLABLE_NON_DISPATCHABLE
    #endif
#endif

/** \struct VmaAllocator
\brief Represents main object of this library initialized.

Fill structure #VmaAllocatorCreateInfo and call function vmaCreateAllocator() to create it.
Call function vmaDestroyAllocator() to destroy it.

It is recommended to create just one object of this type per `VkDevice` object,
right after Vulkan is initialized and keep it alive until before Vulkan device is destroyed.
*/
VK_DEFINE_HANDLE(VmaAllocator)

/// Callback function called after successful vkAllocateMemory.
typedef void (VKAPI_PTR *PFN_vmaAllocateDeviceMemoryFunction)(
    VmaAllocator VMA_NOT_NULL                    allocator,
    uint32_t                                     memoryType,
    VkDeviceMemory VMA_NOT_NULL_NON_DISPATCHABLE memory,
    VkDeviceSize                                 size,
    void* VMA_NULLABLE                           pUserData);
/// Callback function called before vkFreeMemory.
typedef void (VKAPI_PTR *PFN_vmaFreeDeviceMemoryFunction)(
    VmaAllocator VMA_NOT_NULL                    allocator,
    uint32_t                                     memoryType,
    VkDeviceMemory VMA_NOT_NULL_NON_DISPATCHABLE memory,
    VkDeviceSize                                 size,
    void* VMA_NULLABLE                           pUserData);

/** \brief Set of callbacks that the library will call for `vkAllocateMemory` and `vkFreeMemory`.

Provided for informative purpose, e.g. to gather statistics about number of
allocations or total amount of memory allocated in Vulkan.

Used in VmaAllocatorCreateInfo::pDeviceMemoryCallbacks.
*/
typedef struct VmaDeviceMemoryCallbacks {
    /// Optional, can be null.
    PFN_vmaAllocateDeviceMemoryFunction VMA_NULLABLE pfnAllocate;
    /// Optional, can be null.
    PFN_vmaFreeDeviceMemoryFunction VMA_NULLABLE pfnFree;
    /// Optional, can be null.
    void* VMA_NULLABLE pUserData;
} VmaDeviceMemoryCallbacks;

/// Flags for created #VmaAllocator.
typedef enum VmaAllocatorCreateFlagBits {
    /** \brief Allocator and all objects created from it will not be synchronized internally, so you must guarantee they are used from only one thread at a time or synchronized externally by you.

    Using this flag may increase performance because internal mutexes are not used.
    */
    VMA_ALLOCATOR_CREATE_EXTERNALLY_SYNCHRONIZED_BIT = 0x00000001,
    /** \brief Enables usage of VK_KHR_dedicated_allocation extension.

    The flag works only if VmaAllocatorCreateInfo::vulkanApiVersion `== VK_API_VERSION_1_0`.
    When it is `VK_API_VERSION_1_1`, the flag is ignored because the extension has been promoted to Vulkan 1.1.

    Using this extension will automatically allocate dedicated blocks of memory for
    some buffers and images instead of suballocating place for them out of bigger
    memory blocks (as if you explicitly used #VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT
    flag) when it is recommended by the driver. It may improve performance on some
    GPUs.

    You may set this flag only if you found out that following device extensions are
    supported, you enabled them while creating Vulkan device passed as
    VmaAllocatorCreateInfo::device, and you want them to be used internally by this
    library:

    - VK_KHR_get_memory_requirements2 (device extension)
    - VK_KHR_dedicated_allocation (device extension)

    When this flag is set, you can experience following warnings reported by Vulkan
    validation layer. You can ignore them.

    > vkBindBufferMemory(): Binding memory to buffer 0x2d but vkGetBufferMemoryRequirements() has not been called on that buffer.
    */
    VMA_ALLOCATOR_CREATE_KHR_DEDICATED_ALLOCATION_BIT = 0x00000002,
    /**
    Enables usage of VK_KHR_bind_memory2 extension.

    The flag works only if VmaAllocatorCreateInfo::vulkanApiVersion `== VK_API_VERSION_1_0`.
    When it is `VK_API_VERSION_1_1`, the flag is ignored because the extension has been promoted to Vulkan 1.1.

    You may set this flag only if you found out that this device extension is supported,
    you enabled it while creating Vulkan device passed as VmaAllocatorCreateInfo::device,
    and you want it to be used internally by this library.

    The extension provides functions `vkBindBufferMemory2KHR` and `vkBindImageMemory2KHR`,
    which allow to pass a chain of `pNext` structures while binding.
    This flag is required if you use `pNext` parameter in vmaBindBufferMemory2() or vmaBindImageMemory2().
    */
    VMA_ALLOCATOR_CREATE_KHR_BIND_MEMORY2_BIT = 0x00000004,
    /**
    Enables usage of VK_EXT_memory_budget extension.

    You may set this flag only if you found out that this device extension is supported,
    you enabled it while creating Vulkan device passed as VmaAllocatorCreateInfo::device,
    and you want it to be used internally by this library, along with another instance extension
    VK_KHR_get_physical_device_properties2, which is required by it (or Vulkan 1.1, where this extension is promoted).

    The extension provides query for current memory usage and budget, which will probably
    be more accurate than an estimation used by the library otherwise.
    */
    VMA_ALLOCATOR_CREATE_EXT_MEMORY_BUDGET_BIT = 0x00000008,
    /**
    Enables usage of VK_AMD_device_coherent_memory extension.

    You may set this flag only if you:

    - found out that this device extension is supported and enabled it while creating Vulkan device passed as VmaAllocatorCreateInfo::device,
    - checked that `VkPhysicalDeviceCoherentMemoryFeaturesAMD::deviceCoherentMemory` is true and set it while creating the Vulkan device,
    - want it to be used internally by this library.

    The extension and accompanying device feature provide access to memory types with
    `VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD` and `VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD` flags.
    They are useful mostly for writing breadcrumb markers - a common method for debugging GPU crash/hang/TDR.

    When the extension is not enabled, such memory types are still enumerated, but their usage is illegal.
    To protect from this error, if you don't create the allocator with this flag, it will refuse to allocate any memory or create a custom pool in such memory type,
    returning `VK_ERROR_FEATURE_NOT_PRESENT`.
    */
    VMA_ALLOCATOR_CREATE_AMD_DEVICE_COHERENT_MEMORY_BIT = 0x00000010,
    /**
    Enables usage of "buffer device address" feature, which allows you to use function
    `vkGetBufferDeviceAddress*` to get raw GPU pointer to a buffer and pass it for usage inside a shader.

    You may set this flag only if you:

    1. (For Vulkan version < 1.2) Found as available and enabled device extension
    VK_KHR_buffer_device_address.
    This extension is promoted to core Vulkan 1.2.
    2. Found as available and enabled device feature `VkPhysicalDeviceBufferDeviceAddressFeatures::bufferDeviceAddress`.

    When this flag is set, you can create buffers with `VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT` using VMA.
    The library automatically adds `VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT` to
    allocated memory blocks wherever it might be needed.

    For more information, see documentation chapter \ref enabling_buffer_device_address.
    */
    VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT = 0x00000020,
    /**
    Enables usage of VK_EXT_memory_priority extension in the library.

    You may set this flag only if you found available and enabled this device extension,
    along with `VkPhysicalDeviceMemoryPriorityFeaturesEXT::memoryPriority == VK_TRUE`,
    while creating Vulkan device passed as VmaAllocatorCreateInfo::device.

    When this flag is used, VmaAllocationCreateInfo::priority and VmaPoolCreateInfo::priority
    are used to set priorities of allocated Vulkan memory. Without it, these variables are ignored.

    A priority must be a floating-point value between 0 and 1, indicating the priority of the allocation relative to other memory allocations.
    Larger values are higher priority. The granularity of the priorities is implementation-dependent.
    It is automatically passed to every call to `vkAllocateMemory` done by the library using structure `VkMemoryPriorityAllocateInfoEXT`.
    The value to be used for default priority is 0.5.
    For more details, see the documentation of the VK_EXT_memory_priority extension.
    */
    VMA_ALLOCATOR_CREATE_EXT_MEMORY_PRIORITY_BIT = 0x00000040,

    VMA_ALLOCATOR_CREATE_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
} VmaAllocatorCreateFlagBits;
typedef VkFlags VmaAllocatorCreateFlags;

/** \brief Pointers to some Vulkan functions - a subset used by the library.

Used in VmaAllocatorCreateInfo::pVulkanFunctions.
*/
typedef struct VmaVulkanFunctions {
    PFN_vkGetPhysicalDeviceProperties VMA_NULLABLE vkGetPhysicalDeviceProperties;
    PFN_vkGetPhysicalDeviceMemoryProperties VMA_NULLABLE vkGetPhysicalDeviceMemoryProperties;
    PFN_vkAllocateMemory VMA_NULLABLE vkAllocateMemory;
    PFN_vkFreeMemory VMA_NULLABLE vkFreeMemory;
    PFN_vkMapMemory VMA_NULLABLE vkMapMemory;
    PFN_vkUnmapMemory VMA_NULLABLE vkUnmapMemory;
    PFN_vkFlushMappedMemoryRanges VMA_NULLABLE vkFlushMappedMemoryRanges;
    PFN_vkInvalidateMappedMemoryRanges VMA_NULLABLE vkInvalidateMappedMemoryRanges;
    PFN_vkBindBufferMemory VMA_NULLABLE vkBindBufferMemory;
    PFN_vkBindImageMemory VMA_NULLABLE vkBindImageMemory;
    PFN_vkGetBufferMemoryRequirements VMA_NULLABLE vkGetBufferMemoryRequirements;
    PFN_vkGetImageMemoryRequirements VMA_NULLABLE vkGetImageMemoryRequirements;
    PFN_vkCreateBuffer VMA_NULLABLE vkCreateBuffer;
    PFN_vkDestroyBuffer VMA_NULLABLE vkDestroyBuffer;
    PFN_vkCreateImage VMA_NULLABLE vkCreateImage;
    PFN_vkDestroyImage VMA_NULLABLE vkDestroyImage;
    PFN_vkCmdCopyBuffer VMA_NULLABLE vkCmdCopyBuffer;
#if VMA_DEDICATED_ALLOCATION || VMA_VULKAN_VERSION >= 1001000
    PFN_vkGetBufferMemoryRequirements2KHR VMA_NULLABLE vkGetBufferMemoryRequirements2KHR;
    PFN_vkGetImageMemoryRequirements2KHR VMA_NULLABLE vkGetImageMemoryRequirements2KHR;
#endif
#if VMA_BIND_MEMORY2 || VMA_VULKAN_VERSION >= 1001000
    PFN_vkBindBufferMemory2KHR VMA_NULLABLE vkBindBufferMemory2KHR;
    PFN_vkBindImageMemory2KHR VMA_NULLABLE vkBindImageMemory2KHR;
#endif
#if VMA_MEMORY_BUDGET || VMA_VULKAN_VERSION >= 1001000
    PFN_vkGetPhysicalDeviceMemoryProperties2KHR VMA_NULLABLE vkGetPhysicalDeviceMemoryProperties2KHR;
#endif
} VmaVulkanFunctions;

/// Flags to be used in VmaRecordSettings::flags.
typedef enum VmaRecordFlagBits {
    /** \brief Enables flush after recording every function call.

    Enable it if you expect your application to crash, which may leave recording file truncated.
    It may degrade performance though.
    */
    VMA_RECORD_FLUSH_AFTER_CALL_BIT = 0x00000001,

    VMA_RECORD_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
} VmaRecordFlagBits;
typedef VkFlags VmaRecordFlags;

/// Parameters for recording calls to VMA functions. To be used in VmaAllocatorCreateInfo::pRecordSettings.
typedef struct VmaRecordSettings
{
    /// Flags for recording. Use #VmaRecordFlagBits enum.
    VmaRecordFlags flags;
    /** \brief Path to the file that should be written by the recording.

    Suggested extension: "csv".
    If the file already exists, it will be overwritten.
    It will be opened for the whole time #VmaAllocator object is alive.
    If opening this file fails, creation of the whole allocator object fails.
    */
    const char* VMA_NOT_NULL pFilePath;
} VmaRecordSettings;

/// Description of a Allocator to be created.
typedef struct VmaAllocatorCreateInfo
{
    /// Flags for created allocator. Use #VmaAllocatorCreateFlagBits enum.
    VmaAllocatorCreateFlags flags;
    /// Vulkan physical device.
    /** It must be valid throughout whole lifetime of created allocator. */
    VkPhysicalDevice VMA_NOT_NULL physicalDevice;
    /// Vulkan device.
    /** It must be valid throughout whole lifetime of created allocator. */
    VkDevice VMA_NOT_NULL device;
    /// Preferred size of a single `VkDeviceMemory` block to be allocated from large heaps > 1 GiB. Optional.
    /** Set to 0 to use default, which is currently 256 MiB. */
    VkDeviceSize preferredLargeHeapBlockSize;
    /// Custom CPU memory allocation callbacks. Optional.
    /** Optional, can be null. When specified, will also be used for all CPU-side memory allocations. */
    const VkAllocationCallbacks* VMA_NULLABLE pAllocationCallbacks;
    /// Informative callbacks for `vkAllocateMemory`, `vkFreeMemory`. Optional.
    /** Optional, can be null. */
    const VmaDeviceMemoryCallbacks* VMA_NULLABLE pDeviceMemoryCallbacks;
    /** \brief Maximum number of additional frames that are in use at the same time as current frame.

    This value is used only when you make allocations with
    VMA_ALLOCATION_CREATE_CAN_BECOME_LOST_BIT flag. Such allocation cannot become
    lost if allocation.lastUseFrameIndex >= allocator.currentFrameIndex - frameInUseCount.

    For example, if you double-buffer your command buffers, so resources used for
    rendering in previous frame may still be in use by the GPU at the moment you
    allocate resources needed for the current frame, set this value to 1.

    If you want to allow any allocations other than used in the current frame to
    become lost, set this value to 0.
    */
    uint32_t frameInUseCount;
    /** \brief Either null or a pointer to an array of limits on maximum number of bytes that can be allocated out of particular Vulkan memory heap.

    If not NULL, it must be a pointer to an array of
    `VkPhysicalDeviceMemoryProperties::memoryHeapCount` elements, defining limit on
    maximum number of bytes that can be allocated out of particular Vulkan memory
    heap.

    Any of the elements may be equal to `VK_WHOLE_SIZE`, which means no limit on that
    heap. This is also the default in case of `pHeapSizeLimit` = NULL.

    If there is a limit defined for a heap:

    - If user tries to allocate more memory from that heap using this allocator,
      the allocation fails with `VK_ERROR_OUT_OF_DEVICE_MEMORY`.
    - If the limit is smaller than heap size reported in `VkMemoryHeap::size`, the
      value of this limit will be reported instead when using vmaGetMemoryProperties().

    Warning! Using this feature may not be equivalent to installing a GPU with
    smaller amount of memory, because graphics driver doesn't necessary fail new
    allocations with `VK_ERROR_OUT_OF_DEVICE_MEMORY` result when memory capacity is
    exceeded. It may return success and just silently migrate some device memory
    blocks to system RAM. This driver behavior can also be controlled using
    VK_AMD_memory_overallocation_behavior extension.
    */
    const VkDeviceSize* VMA_NULLABLE VMA_LEN_IF_NOT_NULL("VkPhysicalDeviceMemoryProperties::memoryHeapCount") pHeapSizeLimit;

    /** \brief Pointers to Vulkan functions. Can be null.

    For details see [Pointers to Vulkan functions](@ref config_Vulkan_functions).
    */
    const VmaVulkanFunctions* VMA_NULLABLE pVulkanFunctions;
    /** \brief Parameters for recording of VMA calls. Can be null.

    If not null, it enables recording of calls to VMA functions to a file.
    If support for recording is not enabled using `VMA_RECORDING_ENABLED` macro,
    creation of the allocator object fails with `VK_ERROR_FEATURE_NOT_PRESENT`.
    */
    const VmaRecordSettings* VMA_NULLABLE pRecordSettings;
    /** \brief Handle to Vulkan instance object.

    Starting from version 3.0.0 this member is no longer optional, it must be set!
    */
    VkInstance VMA_NOT_NULL instance;
    /** \brief Optional. The highest version of Vulkan that the application is designed to use.

    It must be a value in the format as created by macro `VK_MAKE_VERSION` or a constant like: `VK_API_VERSION_1_1`, `VK_API_VERSION_1_0`.
    The patch version number specified is ignored. Only the major and minor versions are considered.
    It must be less or equal (preferably equal) to value as passed to `vkCreateInstance` as `VkApplicationInfo::apiVersion`.
    Only versions 1.0, 1.1, 1.2 are supported by the current implementation.
    Leaving it initialized to zero is equivalent to `VK_API_VERSION_1_0`.
    */
    uint32_t vulkanApiVersion;
#if VMA_EXTERNAL_MEMORY
    /** \brief Either null or a pointer to an array of external memory handle types for each Vulkan memory type.

    If not NULL, it must be a pointer to an array of `VkPhysicalDeviceMemoryProperties::memoryTypeCount`
    elements, defining external memory handle types of particular Vulkan memory type,
    to be passed using `VkExportMemoryAllocateInfoKHR`.

    Any of the elements may be equal to 0, which means not to use `VkExportMemoryAllocateInfoKHR` on this memory type.
    This is also the default in case of `pTypeExternalMemoryHandleTypes` = NULL.
    */
    const VkExternalMemoryHandleTypeFlagsKHR* VMA_NULLABLE VMA_LEN_IF_NOT_NULL("VkPhysicalDeviceMemoryProperties::memoryTypeCount") pTypeExternalMemoryHandleTypes;
#endif // #if VMA_EXTERNAL_MEMORY
} VmaAllocatorCreateInfo;

/// Creates Allocator object.
VMA_CALL_PRE VkResult VMA_CALL_POST vmaCreateAllocator(
    const VmaAllocatorCreateInfo* VMA_NOT_NULL pCreateInfo,
    VmaAllocator VMA_NULLABLE * VMA_NOT_NULL pAllocator);

/// Destroys allocator object.
VMA_CALL_PRE void VMA_CALL_POST vmaDestroyAllocator(
    VmaAllocator VMA_NULLABLE allocator);

/** \brief Information about existing #VmaAllocator object.
*/
typedef struct VmaAllocatorInfo
{
    /** \brief Handle to Vulkan instance object.

    This is the same value as has been passed through VmaAllocatorCreateInfo::instance.
    */
    VkInstance VMA_NOT_NULL instance;
    /** \brief Handle to Vulkan physical device object.

    This is the same value as has been passed through VmaAllocatorCreateInfo::physicalDevice.
    */
    VkPhysicalDevice VMA_NOT_NULL physicalDevice;
    /** \brief Handle to Vulkan device object.

    This is the same value as has been passed through VmaAllocatorCreateInfo::device.
    */
    VkDevice VMA_NOT_NULL device;
} VmaAllocatorInfo;

/** \brief Returns information about existing #VmaAllocator object - handle to Vulkan device etc.

It might be useful if you want to keep just the #VmaAllocator handle and fetch other required handles to
`VkPhysicalDevice`, `VkDevice` etc. every time using this function.
*/
VMA_CALL_PRE void VMA_CALL_POST vmaGetAllocatorInfo(VmaAllocator VMA_NOT_NULL allocator, VmaAllocatorInfo* VMA_NOT_NULL pAllocatorInfo);

/**
PhysicalDeviceProperties are fetched from physicalDevice by the allocator.
You can access it here, without fetching it again on your own.
*/
VMA_CALL_PRE void VMA_CALL_POST vmaGetPhysicalDeviceProperties(
    VmaAllocator VMA_NOT_NULL allocator,
    const VkPhysicalDeviceProperties* VMA_NULLABLE * VMA_NOT_NULL ppPhysicalDeviceProperties);

/**
PhysicalDeviceMemoryProperties are fetched from physicalDevice by the allocator.
You can access it here, without fetching it again on your own.
*/
VMA_CALL_PRE void VMA_CALL_POST vmaGetMemoryProperties(
    VmaAllocator VMA_NOT_NULL allocator,
    const VkPhysicalDeviceMemoryProperties* VMA_NULLABLE * VMA_NOT_NULL ppPhysicalDeviceMemoryProperties);

/**
\brief Given Memory Type Index, returns Property Flags of this memory type.

This is just a convenience function. Same information can be obtained using
vmaGetMemoryProperties().
*/
VMA_CALL_PRE void VMA_CALL_POST vmaGetMemoryTypeProperties(
    VmaAllocator VMA_NOT_NULL allocator,
    uint32_t memoryTypeIndex,
    VkMemoryPropertyFlags* VMA_NOT_NULL pFlags);

/** \brief Sets index of the current frame.

This function must be used if you make allocations with
#VMA_ALLOCATION_CREATE_CAN_BECOME_LOST_BIT and
#VMA_ALLOCATION_CREATE_CAN_MAKE_OTHER_LOST_BIT flags to inform the allocator
when a new frame begins. Allocations queried using vmaGetAllocationInfo() cannot
become lost in the current frame.
*/
VMA_CALL_PRE void VMA_CALL_POST vmaSetCurrentFrameIndex(
    VmaAllocator VMA_NOT_NULL allocator,
    uint32_t frameIndex);

/** \brief Calculated statistics of memory usage in entire allocator.
*/
typedef struct VmaStatInfo
{
    /// Number of `VkDeviceMemory` Vulkan memory blocks allocated.
    uint32_t blockCount;
    /// Number of #VmaAllocation allocation objects allocated.
    uint32_t allocationCount;
    /// Number of free ranges of memory between allocations.
    uint32_t unusedRangeCount;
    /// Total number of bytes occupied by all allocations.
    VkDeviceSize usedBytes;
    /// Total number of bytes occupied by unused ranges.
    VkDeviceSize unusedBytes;
    VkDeviceSize allocationSizeMin, allocationSizeAvg, allocationSizeMax;
    VkDeviceSize unusedRangeSizeMin, unusedRangeSizeAvg, unusedRangeSizeMax;
} VmaStatInfo;

/// General statistics from current state of Allocator.
typedef struct VmaStats
{
    VmaStatInfo memoryType[VK_MAX_MEMORY_TYPES];
    VmaStatInfo memoryHeap[VK_MAX_MEMORY_HEAPS];
    VmaStatInfo total;
} VmaStats;

/** \brief Retrieves statistics from current state of the Allocator.

This function is called "calculate" not "get" because it has to traverse all
internal data structures, so it may be quite slow. For faster but more brief statistics
suitable to be called every frame or every allocation, use vmaGetBudget().

Note that when using allocator from multiple threads, returned information may immediately
become outdated.
*/
VMA_CALL_PRE void VMA_CALL_POST vmaCalculateStats(
    VmaAllocator VMA_NOT_NULL allocator,
    VmaStats* VMA_NOT_NULL pStats);

/** \brief Statistics of current memory usage and available budget, in bytes, for specific memory heap.
*/
typedef struct VmaBudget
{
    /** \brief Sum size of all `VkDeviceMemory` blocks allocated from particular heap, in bytes.
    */
    VkDeviceSize blockBytes;

    /** \brief Sum size of all allocations created in particular heap, in bytes.

    Usually less or equal than `blockBytes`.
    Difference `blockBytes - allocationBytes` is the amount of memory allocated but unused -
    available for new allocations or wasted due to fragmentation.

    It might be greater than `blockBytes` if there are some allocations in lost state, as they account
    to this value as well.
    */
    VkDeviceSize allocationBytes;

    /** \brief Estimated current memory usage of the program, in bytes.

    Fetched from system using `VK_EXT_memory_budget` extension if enabled.

    It might be different than `blockBytes` (usually higher) due to additional implicit objects
    also occupying the memory, like swapchain, pipelines, descriptor heaps, command buffers, or
    `VkDeviceMemory` blocks allocated outside of this library, if any.
    */
    VkDeviceSize usage;

    /** \brief Estimated amount of memory available to the program, in bytes.

    Fetched from system using `VK_EXT_memory_budget` extension if enabled.

    It might be different (most probably smaller) than `VkMemoryHeap::size[heapIndex]` due to factors
    external to the program, like other programs also consuming system resources.
    Difference `budget - usage` is the amount of additional memory that can probably
    be allocated without problems. Exceeding the budget may result in various problems.
    */
    VkDeviceSize budget;
} VmaBudget;

/** \brief Retrieves information about current memory budget for all memory heaps.

\param allocator
\param[out] pBudget Must point to array with number of elements at least equal to number of memory heaps in physical device used.

This function is called "get" not "calculate" because it is very fast, suitable to be called
every frame or every allocation. For more detailed statistics use vmaCalculateStats().

Note that when using allocator from multiple threads, returned information may immediately
become outdated.
*/
VMA_CALL_PRE void VMA_CALL_POST vmaGetBudget(
    VmaAllocator VMA_NOT_NULL allocator,
    VmaBudget* VMA_NOT_NULL pBudget);

#ifndef VMA_STATS_STRING_ENABLED
#define VMA_STATS_STRING_ENABLED 1
#endif

#if VMA_STATS_STRING_ENABLED

/// Builds and returns statistics as string in JSON format.
/**
@param allocator
@param[out] ppStatsString Must be freed using vmaFreeStatsString() function.
@param detailedMap
*/
VMA_CALL_PRE void VMA_CALL_POST vmaBuildStatsString(
    VmaAllocator VMA_NOT_NULL allocator,
    char* VMA_NULLABLE * VMA_NOT_NULL ppStatsString,
    VkBool32 detailedMap);

VMA_CALL_PRE void VMA_CALL_POST vmaFreeStatsString(
    VmaAllocator VMA_NOT_NULL allocator,
    char* VMA_NULLABLE pStatsString);

#endif // #if VMA_STATS_STRING_ENABLED

/** \struct VmaPool
\brief Represents custom memory pool

Fill structure VmaPoolCreateInfo and call function vmaCreatePool() to create it.
Call function vmaDestroyPool() to destroy it.

For more information see [Custom memory pools](@ref choosing_memory_type_custom_memory_pools).
*/
VK_DEFINE_HANDLE(VmaPool)

typedef enum VmaMemoryUsage
{
    /** No intended memory usage specified.
    Use other members of VmaAllocationCreateInfo to specify your requirements.
    */
    VMA_MEMORY_USAGE_UNKNOWN = 0,
    /** Memory will be used on device only, so fast access from the device is preferred.
    It usually means device-local GPU (video) memory.
    No need to be mappable on host.
    It is roughly equivalent of `D3D12_HEAP_TYPE_DEFAULT`.

    Usage:

    - Resources written and read by device, e.g. images used as attachments.
    - Resources transferred from host once (immutable) or infrequently and read by
      device multiple times, e.g. textures to be sampled, vertex buffers, uniform
      (constant) buffers, and majority of other types of resources used on GPU.

    Allocation may still end up in `HOST_VISIBLE` memory on some implementations.
    In such case, you are free to map it.
    You can use #VMA_ALLOCATION_CREATE_MAPPED_BIT with this usage type.
    */
    VMA_MEMORY_USAGE_GPU_ONLY = 1,
    /** Memory will be mappable on host.
    It usually means CPU (system) memory.
    Guarantees to be `HOST_VISIBLE` and `HOST_COHERENT`.
    CPU access is typically uncached. Writes may be write-combined.
    Resources created in this pool may still be accessible to the device, but access to them can be slow.
    It is roughly equivalent of `D3D12_HEAP_TYPE_UPLOAD`.

    Usage: Staging copy of resources used as transfer source.
    */
    VMA_MEMORY_USAGE_CPU_ONLY = 2,
    /**
    Memory that is both mappable on host (guarantees to be `HOST_VISIBLE`) and preferably fast to access by GPU.
    CPU access is typically uncached. Writes may be write-combined.

    Usage: Resources written frequently by host (dynamic), read by device. E.g. textures (with LINEAR layout), vertex buffers, uniform buffers updated every frame or every draw call.
    */
    VMA_MEMORY_USAGE_CPU_TO_GPU = 3,
    /** Memory mappable on host (guarantees to be `HOST_VISIBLE`) and cached.
    It is roughly equivalent of `D3D12_HEAP_TYPE_READBACK`.

    Usage:

    - Resources written by device, read by host - results of some computations, e.g. screen capture, average scene luminance for HDR tone mapping.
    - Any resources read or accessed randomly on host, e.g. CPU-side copy of vertex buffer used as source of transfer, but also used for collision detection.
    */
    VMA_MEMORY_USAGE_GPU_TO_CPU = 4,
    /** CPU memory - memory that is preferably not `DEVICE_LOCAL`, but also not guaranteed to be `HOST_VISIBLE`.

    Usage: Staging copy of resources moved from GPU memory to CPU memory as part
    of custom paging/residency mechanism, to be moved back to GPU memory when needed.
    */
    VMA_MEMORY_USAGE_CPU_COPY = 5,
    /** Lazily allocated GPU memory having `VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT`.
    Exists mostly on mobile platforms. Using it on desktop PC or other GPUs with no such memory type present will fail the allocation.

    Usage: Memory for transient attachment images (color attachments, depth attachments etc.), created with `VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT`.

    Allocations with this usage are always created as dedicated - it implies #VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT.
    */
    VMA_MEMORY_USAGE_GPU_LAZILY_ALLOCATED = 6,

    VMA_MEMORY_USAGE_MAX_ENUM = 0x7FFFFFFF
} VmaMemoryUsage;

/// Flags to be passed as VmaAllocationCreateInfo::flags.
typedef enum VmaAllocationCreateFlagBits {
    /** \brief Set this flag if the allocation should have its own memory block.

    Use it for special, big resources, like fullscreen images used as attachments.

    You should not use this flag if VmaAllocationCreateInfo::pool is not null.
    */
    VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT = 0x00000001,

    /** \brief Set this flag to only try to allocate from existing `VkDeviceMemory` blocks and never create new such block.

    If new allocation cannot be placed in any of the existing blocks, allocation
    fails with `VK_ERROR_OUT_OF_DEVICE_MEMORY` error.

    You should not use #VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT and
    #VMA_ALLOCATION_CREATE_NEVER_ALLOCATE_BIT at the same time. It makes no sense.

    If VmaAllocationCreateInfo::pool is not null, this flag is implied and ignored. */
    VMA_ALLOCATION_CREATE_NEVER_ALLOCATE_BIT = 0x00000002,
    /** \brief Set this flag to use a memory that will be persistently mapped and retrieve pointer to it.

    Pointer to mapped memory will be returned through VmaAllocationInfo::pMappedData.

    It is valid to use this flag for allocation made from memory type that is not
    `HOST_VISIBLE`. This flag is then ignored and memory is not mapped. This is
    useful if you need an allocation that is efficient to use on GPU
    (`DEVICE_LOCAL`) and still want to map it directly if possible on platforms that
    support it (e.g. Intel GPU).

    You should not use this flag together with #VMA_ALLOCATION_CREATE_CAN_BECOME_LOST_BIT.
    */
    VMA_ALLOCATION_CREATE_MAPPED_BIT = 0x00000004,
    /** Allocation created with this flag can become lost as a result of another
    allocation with #VMA_ALLOCATION_CREATE_CAN_MAKE_OTHER_LOST_BIT flag, so you
    must check it before use.

    To check if allocation is not lost, call vmaGetAllocationInfo() and check if
    VmaAllocationInfo::deviceMemory is not `VK_NULL_HANDLE`.

    For details about supporting lost allocations, see Lost Allocations
    chapter of User Guide on Main Page.

    You should not use this flag together with #VMA_ALLOCATION_CREATE_MAPPED_BIT.
    */
    VMA_ALLOCATION_CREATE_CAN_BECOME_LOST_BIT = 0x00000008,
    /** While creating allocation using this flag, other allocations that were
    created with flag #VMA_ALLOCATION_CREATE_CAN_BECOME_LOST_BIT can become lost.

    For details about supporting lost allocations, see Lost Allocations
    chapter of User Guide on Main Page.
    */
    VMA_ALLOCATION_CREATE_CAN_MAKE_OTHER_LOST_BIT = 0x00000010,
    /** Set this flag to treat VmaAllocationCreateInfo::pUserData as pointer to a
    null-terminated string. Instead of copying pointer value, a local copy of the
    string is made and stored in allocation's `pUserData`. The string is automatically
    freed together with the allocation. It is also used in vmaBuildStatsString().
    */
    VMA_ALLOCATION_CREATE_USER_DATA_COPY_STRING_BIT = 0x00000020,
    /** Allocation will be created from upper stack in a double stack pool.

    This flag is only allowed for custom pools created with #VMA_POOL_CREATE_LINEAR_ALGORITHM_BIT flag.
    */
    VMA_ALLOCATION_CREATE_UPPER_ADDRESS_BIT = 0x00000040,
    /** Create both buffer/image and allocation, but don't bind them together.
    It is useful when you want to bind yourself to do some more advanced binding, e.g. using some extensions.
    The flag is meaningful only with functions that bind by default: vmaCreateBuffer(), vmaCreateImage().
    Otherwise it is ignored.
    */
    VMA_ALLOCATION_CREATE_DONT_BIND_BIT = 0x00000080,
    /** Create allocation only if additional device memory required for it, if any, won't exceed
    memory budget. Otherwise return `VK_ERROR_OUT_OF_DEVICE_MEMORY`.
    */
    VMA_ALLOCATION_CREATE_WITHIN_BUDGET_BIT = 0x00000100,

    /** Allocation strategy that chooses smallest possible free range for the
    allocation.
    */
    VMA_ALLOCATION_CREATE_STRATEGY_BEST_FIT_BIT  = 0x00010000,
    /** Allocation strategy that chooses biggest possible free range for the
    allocation.
    */
    VMA_ALLOCATION_CREATE_STRATEGY_WORST_FIT_BIT = 0x00020000,
    /** Allocation strategy that chooses first suitable free range for the
    allocation.

    "First" doesn't necessarily means the one with smallest offset in memory,
    but rather the one that is easiest and fastest to find.
    */
    VMA_ALLOCATION_CREATE_STRATEGY_FIRST_FIT_BIT = 0x00040000,

    /** Allocation strategy that tries to minimize memory usage.
    */
    VMA_ALLOCATION_CREATE_STRATEGY_MIN_MEMORY_BIT = VMA_ALLOCATION_CREATE_STRATEGY_BEST_FIT_BIT,
    /** Allocation strategy that tries to minimize allocation time.
    */
    VMA_ALLOCATION_CREATE_STRATEGY_MIN_TIME_BIT = VMA_ALLOCATION_CREATE_STRATEGY_FIRST_FIT_BIT,
    /** Allocation strategy that tries to minimize memory fragmentation.
    */
    VMA_ALLOCATION_CREATE_STRATEGY_MIN_FRAGMENTATION_BIT = VMA_ALLOCATION_CREATE_STRATEGY_WORST_FIT_BIT,

    /** A bit mask to extract only `STRATEGY` bits from entire set of flags.
    */
    VMA_ALLOCATION_CREATE_STRATEGY_MASK =
        VMA_ALLOCATION_CREATE_STRATEGY_BEST_FIT_BIT |
        VMA_ALLOCATION_CREATE_STRATEGY_WORST_FIT_BIT |
        VMA_ALLOCATION_CREATE_STRATEGY_FIRST_FIT_BIT,

    VMA_ALLOCATION_CREATE_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
} VmaAllocationCreateFlagBits;
typedef VkFlags VmaAllocationCreateFlags;

typedef struct VmaAllocationCreateInfo
{
    /// Use #VmaAllocationCreateFlagBits enum.
    VmaAllocationCreateFlags flags;
    /** \brief Intended usage of memory.

    You can leave #VMA_MEMORY_USAGE_UNKNOWN if you specify memory requirements in other way. \n
    If `pool` is not null, this member is ignored.
    */
    VmaMemoryUsage usage;
    /** \brief Flags that must be set in a Memory Type chosen for an allocation.

    Leave 0 if you specify memory requirements in other way. \n
    If `pool` is not null, this member is ignored.*/
    VkMemoryPropertyFlags requiredFlags;
    /** \brief Flags that preferably should be set in a memory type chosen for an allocation.

    Set to 0 if no additional flags are preferred. \n
    If `pool` is not null, this member is ignored. */
    VkMemoryPropertyFlags preferredFlags;
    /** \brief Bitmask containing one bit set for every memory type acceptable for this allocation.

    Value 0 is equivalent to `UINT32_MAX` - it means any memory type is accepted if
    it meets other requirements specified by this structure, with no further
    restrictions on memory type index. \n
    If `pool` is not null, this member is ignored.
    */
    uint32_t memoryTypeBits;
    /** \brief Pool that this allocation should be created in.

    Leave `VK_NULL_HANDLE` to allocate from default pool. If not null, members:
    `usage`, `requiredFlags`, `preferredFlags`, `memoryTypeBits` are ignored.
    */
    VmaPool VMA_NULLABLE pool;
    /** \brief Custom general-purpose pointer that will be stored in #VmaAllocation, can be read as VmaAllocationInfo::pUserData and changed using vmaSetAllocationUserData().

    If #VMA_ALLOCATION_CREATE_USER_DATA_COPY_STRING_BIT is used, it must be either
    null or pointer to a null-terminated string. The string will be then copied to
    internal buffer, so it doesn't need to be valid after allocation call.
    */
    void* VMA_NULLABLE pUserData;
    /** \brief A floating-point value between 0 and 1, indicating the priority of the allocation relative to other memory allocations.

    It is used only when #VMA_ALLOCATOR_CREATE_EXT_MEMORY_PRIORITY_BIT flag was used during creation of the #VmaAllocator object
    and this allocation ends up as dedicated or is explicitly forced as dedicated using #VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT.
    Otherwise, it has the priority of a memory block where it is placed and this variable is ignored.
    */
    float priority;
} VmaAllocationCreateInfo;

/**
\brief Helps to find memoryTypeIndex, given memoryTypeBits and VmaAllocationCreateInfo.

This algorithm tries to find a memory type that:

- Is allowed by memoryTypeBits.
- Contains all the flags from pAllocationCreateInfo->requiredFlags.
- Matches intended usage.
- Has as many flags from pAllocationCreateInfo->preferredFlags as possible.

\return Returns VK_ERROR_FEATURE_NOT_PRESENT if not found. Receiving such result
from this function or any other allocating function probably means that your
device doesn't support any memory type with requested features for the specific
type of resource you want to use it for. Please check parameters of your
resource, like image layout (OPTIMAL versus LINEAR) or mip level count.
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaFindMemoryTypeIndex(
    VmaAllocator VMA_NOT_NULL allocator,
    uint32_t memoryTypeBits,
    const VmaAllocationCreateInfo* VMA_NOT_NULL pAllocationCreateInfo,
    uint32_t* VMA_NOT_NULL pMemoryTypeIndex);

/**
\brief Helps to find memoryTypeIndex, given VkBufferCreateInfo and VmaAllocationCreateInfo.

It can be useful e.g. to determine value to be used as VmaPoolCreateInfo::memoryTypeIndex.
It internally creates a temporary, dummy buffer that never has memory bound.
It is just a convenience function, equivalent to calling:

- `vkCreateBuffer`
- `vkGetBufferMemoryRequirements`
- `vmaFindMemoryTypeIndex`
- `vkDestroyBuffer`
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaFindMemoryTypeIndexForBufferInfo(
    VmaAllocator VMA_NOT_NULL allocator,
    const VkBufferCreateInfo* VMA_NOT_NULL pBufferCreateInfo,
    const VmaAllocationCreateInfo* VMA_NOT_NULL pAllocationCreateInfo,
    uint32_t* VMA_NOT_NULL pMemoryTypeIndex);

/**
\brief Helps to find memoryTypeIndex, given VkImageCreateInfo and VmaAllocationCreateInfo.

It can be useful e.g. to determine value to be used as VmaPoolCreateInfo::memoryTypeIndex.
It internally creates a temporary, dummy image that never has memory bound.
It is just a convenience function, equivalent to calling:

- `vkCreateImage`
- `vkGetImageMemoryRequirements`
- `vmaFindMemoryTypeIndex`
- `vkDestroyImage`
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaFindMemoryTypeIndexForImageInfo(
    VmaAllocator VMA_NOT_NULL allocator,
    const VkImageCreateInfo* VMA_NOT_NULL pImageCreateInfo,
    const VmaAllocationCreateInfo* VMA_NOT_NULL pAllocationCreateInfo,
    uint32_t* VMA_NOT_NULL pMemoryTypeIndex);

/// Flags to be passed as VmaPoolCreateInfo::flags.
typedef enum VmaPoolCreateFlagBits {
    /** \brief Use this flag if you always allocate only buffers and linear images or only optimal images out of this pool and so Buffer-Image Granularity can be ignored.

    This is an optional optimization flag.

    If you always allocate using vmaCreateBuffer(), vmaCreateImage(),
    vmaAllocateMemoryForBuffer(), then you don't need to use it because allocator
    knows exact type of your allocations so it can handle Buffer-Image Granularity
    in the optimal way.

    If you also allocate using vmaAllocateMemoryForImage() or vmaAllocateMemory(),
    exact type of such allocations is not known, so allocator must be conservative
    in handling Buffer-Image Granularity, which can lead to suboptimal allocation
    (wasted memory). In that case, if you can make sure you always allocate only
    buffers and linear images or only optimal images out of this pool, use this flag
    to make allocator disregard Buffer-Image Granularity and so make allocations
    faster and more optimal.
    */
    VMA_POOL_CREATE_IGNORE_BUFFER_IMAGE_GRANULARITY_BIT = 0x00000002,

    /** \brief Enables alternative, linear allocation algorithm in this pool.

    Specify this flag to enable linear allocation algorithm, which always creates
    new allocations after last one and doesn't reuse space from allocations freed in
    between. It trades memory consumption for simplified algorithm and data
    structure, which has better performance and uses less memory for metadata.

    By using this flag, you can achieve behavior of free-at-once, stack,
    ring buffer, and double stack. For details, see documentation chapter
    \ref linear_algorithm.

    When using this flag, you must specify VmaPoolCreateInfo::maxBlockCount == 1 (or 0 for default).

    For more details, see [Linear allocation algorithm](@ref linear_algorithm).
    */
    VMA_POOL_CREATE_LINEAR_ALGORITHM_BIT = 0x00000004,

    /** \brief Enables alternative, buddy allocation algorithm in this pool.

    It operates on a tree of blocks, each having size that is a power of two and
    a half of its parent's size. Comparing to default algorithm, this one provides
    faster allocation and deallocation and decreased external fragmentation,
    at the expense of more memory wasted (internal fragmentation).

    For more details, see [Buddy allocation algorithm](@ref buddy_algorithm).
    */
    VMA_POOL_CREATE_BUDDY_ALGORITHM_BIT = 0x00000008,

    /** Bit mask to extract only `ALGORITHM` bits from entire set of flags.
    */
    VMA_POOL_CREATE_ALGORITHM_MASK =
        VMA_POOL_CREATE_LINEAR_ALGORITHM_BIT |
        VMA_POOL_CREATE_BUDDY_ALGORITHM_BIT,

    VMA_POOL_CREATE_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
} VmaPoolCreateFlagBits;
typedef VkFlags VmaPoolCreateFlags;

/** \brief Describes parameter of created #VmaPool.
*/
typedef struct VmaPoolCreateInfo {
    /** \brief Vulkan memory type index to allocate this pool from.
    */
    uint32_t memoryTypeIndex;
    /** \brief Use combination of #VmaPoolCreateFlagBits.
    */
    VmaPoolCreateFlags flags;
    /** \brief Size of a single `VkDeviceMemory` block to be allocated as part of this pool, in bytes. Optional.

    Specify nonzero to set explicit, constant size of memory blocks used by this
    pool.

    Leave 0 to use default and let the library manage block sizes automatically.
    Sizes of particular blocks may vary.
    */
    VkDeviceSize blockSize;
    /** \brief Minimum number of blocks to be always allocated in this pool, even if they stay empty.

    Set to 0 to have no preallocated blocks and allow the pool be completely empty.
    */
    size_t minBlockCount;
    /** \brief Maximum number of blocks that can be allocated in this pool. Optional.

    Set to 0 to use default, which is `SIZE_MAX`, which means no limit.

    Set to same value as VmaPoolCreateInfo::minBlockCount to have fixed amount of memory allocated
    throughout whole lifetime of this pool.
    */
    size_t maxBlockCount;
    /** \brief Maximum number of additional frames that are in use at the same time as current frame.

    This value is used only when you make allocations with
    #VMA_ALLOCATION_CREATE_CAN_BECOME_LOST_BIT flag. Such allocation cannot become
    lost if allocation.lastUseFrameIndex >= allocator.currentFrameIndex - frameInUseCount.

    For example, if you double-buffer your command buffers, so resources used for
    rendering in previous frame may still be in use by the GPU at the moment you
    allocate resources needed for the current frame, set this value to 1.

    If you want to allow any allocations other than used in the current frame to
    become lost, set this value to 0.
    */
    uint32_t frameInUseCount;
    /** \brief A floating-point value between 0 and 1, indicating the priority of the allocations in this pool relative to other memory allocations.

    It is used only when #VMA_ALLOCATOR_CREATE_EXT_MEMORY_PRIORITY_BIT flag was used during creation of the #VmaAllocator object.
    Otherwise, this variable is ignored.
    */
    float priority;
    /** \brief Additional minimum alignment to be used for all allocations created from this pool. Can be 0.

    Leave 0 (default) not to impose any additional alignment. If not 0, it must be a power of two.
    It can be useful in cases where alignment returned by Vulkan by functions like `vkGetBufferMemoryRequirements` is not enough,
    e.g. when doing interop with OpenGL.
    */
    VkDeviceSize minAllocationAlignment;
    /** \brief Additional `pNext` chain to be attached to `VkMemoryAllocateInfo` used for every allocation made by this pool. Optional.

    Optional, can be null. If not null, it must point to a `pNext` chain of structures that can be attached to `VkMemoryAllocateInfo`.
    It can be useful for special needs such as adding `VkExportMemoryAllocateInfoKHR`.
    Structures pointed by this member must remain alive and unchanged for the whole lifetime of the custom pool.

    Please note that some structures, e.g. `VkMemoryPriorityAllocateInfoEXT`, `VkMemoryDedicatedAllocateInfoKHR`,
    can be attached automatically by this library when using other, more convenient of its features.
    */
    void* VMA_NULLABLE pMemoryAllocateNext;
} VmaPoolCreateInfo;

/** \brief Describes parameter of existing #VmaPool.
*/
typedef struct VmaPoolStats {
    /** \brief Total amount of `VkDeviceMemory` allocated from Vulkan for this pool, in bytes.
    */
    VkDeviceSize size;
    /** \brief Total number of bytes in the pool not used by any #VmaAllocation.
    */
    VkDeviceSize unusedSize;
    /** \brief Number of #VmaAllocation objects created from this pool that were not destroyed or lost.
    */
    size_t allocationCount;
    /** \brief Number of continuous memory ranges in the pool not used by any #VmaAllocation.
    */
    size_t unusedRangeCount;
    /** \brief Size of the largest continuous free memory region available for new allocation.

    Making a new allocation of that size is not guaranteed to succeed because of
    possible additional margin required to respect alignment and buffer/image
    granularity.
    */
    VkDeviceSize unusedRangeSizeMax;
    /** \brief Number of `VkDeviceMemory` blocks allocated for this pool.
    */
    size_t blockCount;
} VmaPoolStats;

/** \brief Allocates Vulkan device memory and creates #VmaPool object.

@param allocator Allocator object.
@param pCreateInfo Parameters of pool to create.
@param[out] pPool Handle to created pool.
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaCreatePool(
    VmaAllocator VMA_NOT_NULL allocator,
    const VmaPoolCreateInfo* VMA_NOT_NULL pCreateInfo,
    VmaPool VMA_NULLABLE * VMA_NOT_NULL pPool);

/** \brief Destroys #VmaPool object and frees Vulkan device memory.
*/
VMA_CALL_PRE void VMA_CALL_POST vmaDestroyPool(
    VmaAllocator VMA_NOT_NULL allocator,
    VmaPool VMA_NULLABLE pool);

/** \brief Retrieves statistics of existing #VmaPool object.

@param allocator Allocator object.
@param pool Pool object.
@param[out] pPoolStats Statistics of specified pool.
*/
VMA_CALL_PRE void VMA_CALL_POST vmaGetPoolStats(
    VmaAllocator VMA_NOT_NULL allocator,
    VmaPool VMA_NOT_NULL pool,
    VmaPoolStats* VMA_NOT_NULL pPoolStats);

/** \brief Marks all allocations in given pool as lost if they are not used in current frame or VmaPoolCreateInfo::frameInUseCount back from now.

@param allocator Allocator object.
@param pool Pool.
@param[out] pLostAllocationCount Number of allocations marked as lost. Optional - pass null if you don't need this information.
*/
VMA_CALL_PRE void VMA_CALL_POST vmaMakePoolAllocationsLost(
    VmaAllocator VMA_NOT_NULL allocator,
    VmaPool VMA_NOT_NULL pool,
    size_t* VMA_NULLABLE pLostAllocationCount);

/** \brief Checks magic number in margins around all allocations in given memory pool in search for corruptions.

Corruption detection is enabled only when `VMA_DEBUG_DETECT_CORRUPTION` macro is defined to nonzero,
`VMA_DEBUG_MARGIN` is defined to nonzero and the pool is created in memory type that is
`HOST_VISIBLE` and `HOST_COHERENT`. For more information, see [Corruption detection](@ref debugging_memory_usage_corruption_detection).

Possible return values:

- `VK_ERROR_FEATURE_NOT_PRESENT` - corruption detection is not enabled for specified pool.
- `VK_SUCCESS` - corruption detection has been performed and succeeded.
- `VK_ERROR_UNKNOWN` - corruption detection has been performed and found memory corruptions around one of the allocations.
  `VMA_ASSERT` is also fired in that case.
- Other value: Error returned by Vulkan, e.g. memory mapping failure.
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaCheckPoolCorruption(VmaAllocator VMA_NOT_NULL allocator, VmaPool VMA_NOT_NULL pool);

/** \brief Retrieves name of a custom pool.

After the call `ppName` is either null or points to an internally-owned null-terminated string
containing name of the pool that was previously set. The pointer becomes invalid when the pool is
destroyed or its name is changed using vmaSetPoolName().
*/
VMA_CALL_PRE void VMA_CALL_POST vmaGetPoolName(
    VmaAllocator VMA_NOT_NULL allocator,
    VmaPool VMA_NOT_NULL pool,
    const char* VMA_NULLABLE * VMA_NOT_NULL ppName);

/** \brief Sets name of a custom pool.

`pName` can be either null or pointer to a null-terminated string with new name for the pool.
Function makes internal copy of the string, so it can be changed or freed immediately after this call.
*/
VMA_CALL_PRE void VMA_CALL_POST vmaSetPoolName(
    VmaAllocator VMA_NOT_NULL allocator,
    VmaPool VMA_NOT_NULL pool,
    const char* VMA_NULLABLE pName);

/** \struct VmaAllocation
\brief Represents single memory allocation.

It may be either dedicated block of `VkDeviceMemory` or a specific region of a bigger block of this type
plus unique offset.

There are multiple ways to create such object.
You need to fill structure VmaAllocationCreateInfo.
For more information see [Choosing memory type](@ref choosing_memory_type).

Although the library provides convenience functions that create Vulkan buffer or image,
allocate memory for it and bind them together,
binding of the allocation to a buffer or an image is out of scope of the allocation itself.
Allocation object can exist without buffer/image bound,
binding can be done manually by the user, and destruction of it can be done
independently of destruction of the allocation.

The object also remembers its size and some other information.
To retrieve this information, use function vmaGetAllocationInfo() and inspect
returned structure VmaAllocationInfo.

Some kinds allocations can be in lost state.
For more information, see [Lost allocations](@ref lost_allocations).
*/
VK_DEFINE_HANDLE(VmaAllocation)

/** \brief Parameters of #VmaAllocation objects, that can be retrieved using function vmaGetAllocationInfo().
*/
typedef struct VmaAllocationInfo {
    /** \brief Memory type index that this allocation was allocated from.

    It never changes.
    */
    uint32_t memoryType;
    /** \brief Handle to Vulkan memory object.

    Same memory object can be shared by multiple allocations.

    It can change after call to vmaDefragment() if this allocation is passed to the function, or if allocation is lost.

    If the allocation is lost, it is equal to `VK_NULL_HANDLE`.
    */
    VkDeviceMemory VMA_NULLABLE_NON_DISPATCHABLE deviceMemory;
    /** \brief Offset in `VkDeviceMemory` object to the beginning of this allocation, in bytes. `(deviceMemory, offset)` pair is unique to this allocation.

    You usually don't need to use this offset. If you create a buffer or an image together with the allocation using e.g. function
    vmaCreateBuffer(), vmaCreateImage(), functions that operate on these resources refer to the beginning of the buffer or image,
    not entire device memory block. Functions like vmaMapMemory(), vmaBindBufferMemory() also refer to the beginning of the allocation
    and apply this offset automatically.

    It can change after call to vmaDefragment() if this allocation is passed to the function, or if allocation is lost.
    */
    VkDeviceSize offset;
    /** \brief Size of this allocation, in bytes.

    It never changes, unless allocation is lost.

    \note Allocation size returned in this variable may be greater than the size
    requested for the resource e.g. as `VkBufferCreateInfo::size`. Whole size of the
    allocation is accessible for operations on memory e.g. using a pointer after
    mapping with vmaMapMemory(), but operations on the resource e.g. using
    `vkCmdCopyBuffer` must be limited to the size of the resource.
    */
    VkDeviceSize size;
    /** \brief Pointer to the beginning of this allocation as mapped data.

    If the allocation hasn't been mapped using vmaMapMemory() and hasn't been
    created with #VMA_ALLOCATION_CREATE_MAPPED_BIT flag, this value is null.

    It can change after call to vmaMapMemory(), vmaUnmapMemory().
    It can also change after call to vmaDefragment() if this allocation is passed to the function.
    */
    void* VMA_NULLABLE pMappedData;
    /** \brief Custom general-purpose pointer that was passed as VmaAllocationCreateInfo::pUserData or set using vmaSetAllocationUserData().

    It can change after call to vmaSetAllocationUserData() for this allocation.
    */
    void* VMA_NULLABLE pUserData;
} VmaAllocationInfo;

/** \brief General purpose memory allocation.

@param allocator
@param pVkMemoryRequirements
@param pCreateInfo
@param[out] pAllocation Handle to allocated memory.
@param[out] pAllocationInfo Optional. Information about allocated memory. It can be later fetched using function vmaGetAllocationInfo().

You should free the memory using vmaFreeMemory() or vmaFreeMemoryPages().

It is recommended to use vmaAllocateMemoryForBuffer(), vmaAllocateMemoryForImage(),
vmaCreateBuffer(), vmaCreateImage() instead whenever possible.
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaAllocateMemory(
    VmaAllocator VMA_NOT_NULL allocator,
    const VkMemoryRequirements* VMA_NOT_NULL pVkMemoryRequirements,
    const VmaAllocationCreateInfo* VMA_NOT_NULL pCreateInfo,
    VmaAllocation VMA_NULLABLE * VMA_NOT_NULL pAllocation,
    VmaAllocationInfo* VMA_NULLABLE pAllocationInfo);

/** \brief General purpose memory allocation for multiple allocation objects at once.

@param allocator Allocator object.
@param pVkMemoryRequirements Memory requirements for each allocation.
@param pCreateInfo Creation parameters for each alloction.
@param allocationCount Number of allocations to make.
@param[out] pAllocations Pointer to array that will be filled with handles to created allocations.
@param[out] pAllocationInfo Optional. Pointer to array that will be filled with parameters of created allocations.

You should free the memory using vmaFreeMemory() or vmaFreeMemoryPages().

Word "pages" is just a suggestion to use this function to allocate pieces of memory needed for sparse binding.
It is just a general purpose allocation function able to make multiple allocations at once.
It may be internally optimized to be more efficient than calling vmaAllocateMemory() `allocationCount` times.

All allocations are made using same parameters. All of them are created out of the same memory pool and type.
If any allocation fails, all allocations already made within this function call are also freed, so that when
returned result is not `VK_SUCCESS`, `pAllocation` array is always entirely filled with `VK_NULL_HANDLE`.
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaAllocateMemoryPages(
    VmaAllocator VMA_NOT_NULL allocator,
    const VkMemoryRequirements* VMA_NOT_NULL VMA_LEN_IF_NOT_NULL(allocationCount) pVkMemoryRequirements,
    const VmaAllocationCreateInfo* VMA_NOT_NULL VMA_LEN_IF_NOT_NULL(allocationCount) pCreateInfo,
    size_t allocationCount,
    VmaAllocation VMA_NULLABLE * VMA_NOT_NULL VMA_LEN_IF_NOT_NULL(allocationCount) pAllocations,
    VmaAllocationInfo* VMA_NULLABLE VMA_LEN_IF_NOT_NULL(allocationCount) pAllocationInfo);

/**
@param allocator
@param buffer
@param pCreateInfo
@param[out] pAllocation Handle to allocated memory.
@param[out] pAllocationInfo Optional. Information about allocated memory. It can be later fetched using function vmaGetAllocationInfo().

You should free the memory using vmaFreeMemory().
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaAllocateMemoryForBuffer(
    VmaAllocator VMA_NOT_NULL allocator,
    VkBuffer VMA_NOT_NULL_NON_DISPATCHABLE buffer,
    const VmaAllocationCreateInfo* VMA_NOT_NULL pCreateInfo,
    VmaAllocation VMA_NULLABLE * VMA_NOT_NULL pAllocation,
    VmaAllocationInfo* VMA_NULLABLE pAllocationInfo);

/// Function similar to vmaAllocateMemoryForBuffer().
VMA_CALL_PRE VkResult VMA_CALL_POST vmaAllocateMemoryForImage(
    VmaAllocator VMA_NOT_NULL allocator,
    VkImage VMA_NOT_NULL_NON_DISPATCHABLE image,
    const VmaAllocationCreateInfo* VMA_NOT_NULL pCreateInfo,
    VmaAllocation VMA_NULLABLE * VMA_NOT_NULL pAllocation,
    VmaAllocationInfo* VMA_NULLABLE pAllocationInfo);

/** \brief Frees memory previously allocated using vmaAllocateMemory(), vmaAllocateMemoryForBuffer(), or vmaAllocateMemoryForImage().

Passing `VK_NULL_HANDLE` as `allocation` is valid. Such function call is just skipped.
*/
VMA_CALL_PRE void VMA_CALL_POST vmaFreeMemory(
    VmaAllocator VMA_NOT_NULL allocator,
    const VmaAllocation VMA_NULLABLE allocation);

/** \brief Frees memory and destroys multiple allocations.

Word "pages" is just a suggestion to use this function to free pieces of memory used for sparse binding.
It is just a general purpose function to free memory and destroy allocations made using e.g. vmaAllocateMemory(),
vmaAllocateMemoryPages() and other functions.
It may be internally optimized to be more efficient than calling vmaFreeMemory() `allocationCount` times.

Allocations in `pAllocations` array can come from any memory pools and types.
Passing `VK_NULL_HANDLE` as elements of `pAllocations` array is valid. Such entries are just skipped.
*/
VMA_CALL_PRE void VMA_CALL_POST vmaFreeMemoryPages(
    VmaAllocator VMA_NOT_NULL allocator,
    size_t allocationCount,
    const VmaAllocation VMA_NULLABLE * VMA_NOT_NULL VMA_LEN_IF_NOT_NULL(allocationCount) pAllocations);

/** \brief Returns current information about specified allocation and atomically marks it as used in current frame.

Current paramteres of given allocation are returned in `pAllocationInfo`.

This function also atomically "touches" allocation - marks it as used in current frame,
just like vmaTouchAllocation().
If the allocation is in lost state, `pAllocationInfo->deviceMemory == VK_NULL_HANDLE`.

Although this function uses atomics and doesn't lock any mutex, so it should be quite efficient,
you can avoid calling it too often.

- You can retrieve same VmaAllocationInfo structure while creating your resource, from function
  vmaCreateBuffer(), vmaCreateImage(). You can remember it if you are sure parameters don't change
  (e.g. due to defragmentation or allocation becoming lost).
- If you just want to check if allocation is not lost, vmaTouchAllocation() will work faster.
*/
VMA_CALL_PRE void VMA_CALL_POST vmaGetAllocationInfo(
    VmaAllocator VMA_NOT_NULL allocator,
    VmaAllocation VMA_NOT_NULL allocation,
    VmaAllocationInfo* VMA_NOT_NULL pAllocationInfo);

/** \brief Returns `VK_TRUE` if allocation is not lost and atomically marks it as used in current frame.

If the allocation has been created with #VMA_ALLOCATION_CREATE_CAN_BECOME_LOST_BIT flag,
this function returns `VK_TRUE` if it is not in lost state, so it can still be used.
It then also atomically "touches" the allocation - marks it as used in current frame,
so that you can be sure it won't become lost in current frame or next `frameInUseCount` frames.

If the allocation is in lost state, the function returns `VK_FALSE`.
Memory of such allocation, as well as buffer or image bound to it, should not be used.
Lost allocation and the buffer/image still need to be destroyed.

If the allocation has been created without #VMA_ALLOCATION_CREATE_CAN_BECOME_LOST_BIT flag,
this function always returns `VK_TRUE`.
*/
VMA_CALL_PRE VkBool32 VMA_CALL_POST vmaTouchAllocation(
    VmaAllocator VMA_NOT_NULL allocator,
    VmaAllocation VMA_NOT_NULL allocation);

/** \brief Sets pUserData in given allocation to new value.

If the allocation was created with VMA_ALLOCATION_CREATE_USER_DATA_COPY_STRING_BIT,
pUserData must be either null, or pointer to a null-terminated string. The function
makes local copy of the string and sets it as allocation's `pUserData`. String
passed as pUserData doesn't need to be valid for whole lifetime of the allocation -
you can free it after this call. String previously pointed by allocation's
pUserData is freed from memory.

If the flag was not used, the value of pointer `pUserData` is just copied to
allocation's `pUserData`. It is opaque, so you can use it however you want - e.g.
as a pointer, ordinal number or some handle to you own data.
*/
VMA_CALL_PRE void VMA_CALL_POST vmaSetAllocationUserData(
    VmaAllocator VMA_NOT_NULL allocator,
    VmaAllocation VMA_NOT_NULL allocation,
    void* VMA_NULLABLE pUserData);

/** \brief Creates new allocation that is in lost state from the beginning.

It can be useful if you need a dummy, non-null allocation.

You still need to destroy created object using vmaFreeMemory().

Returned allocation is not tied to any specific memory pool or memory type and
not bound to any image or buffer. It has size = 0. It cannot be turned into
a real, non-empty allocation.
*/
VMA_CALL_PRE void VMA_CALL_POST vmaCreateLostAllocation(
    VmaAllocator VMA_NOT_NULL allocator,
    VmaAllocation VMA_NULLABLE * VMA_NOT_NULL pAllocation);

/** \brief Maps memory represented by given allocation and returns pointer to it.

Maps memory represented by given allocation to make it accessible to CPU code.
When succeeded, `*ppData` contains pointer to first byte of this memory.
If the allocation is part of bigger `VkDeviceMemory` block, the pointer is
correctly offsetted to the beginning of region assigned to this particular
allocation.

Mapping is internally reference-counted and synchronized, so despite raw Vulkan
function `vkMapMemory()` cannot be used to map same block of `VkDeviceMemory`
multiple times simultaneously, it is safe to call this function on allocations
assigned to the same memory block. Actual Vulkan memory will be mapped on first
mapping and unmapped on last unmapping.

If the function succeeded, you must call vmaUnmapMemory() to unmap the
allocation when mapping is no longer needed or before freeing the allocation, at
the latest.

It also safe to call this function multiple times on the same allocation. You
must call vmaUnmapMemory() same number of times as you called vmaMapMemory().

It is also safe to call this function on allocation created with
#VMA_ALLOCATION_CREATE_MAPPED_BIT flag. Its memory stays mapped all the time.
You must still call vmaUnmapMemory() same number of times as you called
vmaMapMemory(). You must not call vmaUnmapMemory() additional time to free the
"0-th" mapping made automatically due to #VMA_ALLOCATION_CREATE_MAPPED_BIT flag.

This function fails when used on allocation made in memory type that is not
`HOST_VISIBLE`.

This function always fails when called for allocation that was created with
#VMA_ALLOCATION_CREATE_CAN_BECOME_LOST_BIT flag. Such allocations cannot be
mapped.

This function doesn't automatically flush or invalidate caches.
If the allocation is made from a memory types that is not `HOST_COHERENT`,
you also need to use vmaInvalidateAllocation() / vmaFlushAllocation(), as required by Vulkan specification.
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaMapMemory(
    VmaAllocator VMA_NOT_NULL allocator,
    VmaAllocation VMA_NOT_NULL allocation,
    void* VMA_NULLABLE * VMA_NOT_NULL ppData);

/** \brief Unmaps memory represented by given allocation, mapped previously using vmaMapMemory().

For details, see description of vmaMapMemory().

This function doesn't automatically flush or invalidate caches.
If the allocation is made from a memory types that is not `HOST_COHERENT`,
you also need to use vmaInvalidateAllocation() / vmaFlushAllocation(), as required by Vulkan specification.
*/
VMA_CALL_PRE void VMA_CALL_POST vmaUnmapMemory(
    VmaAllocator VMA_NOT_NULL allocator,
    VmaAllocation VMA_NOT_NULL allocation);

/** \brief Flushes memory of given allocation.

Calls `vkFlushMappedMemoryRanges()` for memory associated with given range of given allocation.
It needs to be called after writing to a mapped memory for memory types that are not `HOST_COHERENT`.
Unmap operation doesn't do that automatically.

- `offset` must be relative to the beginning of allocation.
- `size` can be `VK_WHOLE_SIZE`. It means all memory from `offset` the the end of given allocation.
- `offset` and `size` don't have to be aligned.
  They are internally rounded down/up to multiply of `nonCoherentAtomSize`.
- If `size` is 0, this call is ignored.
- If memory type that the `allocation` belongs to is not `HOST_VISIBLE` or it is `HOST_COHERENT`,
  this call is ignored.

Warning! `offset` and `size` are relative to the contents of given `allocation`.
If you mean whole allocation, you can pass 0 and `VK_WHOLE_SIZE`, respectively.
Do not pass allocation's offset as `offset`!!!

This function returns the `VkResult` from `vkFlushMappedMemoryRanges` if it is
called, otherwise `VK_SUCCESS`.
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaFlushAllocation(
    VmaAllocator VMA_NOT_NULL allocator,
    VmaAllocation VMA_NOT_NULL allocation,
    VkDeviceSize offset,
    VkDeviceSize size);

/** \brief Invalidates memory of given allocation.

Calls `vkInvalidateMappedMemoryRanges()` for memory associated with given range of given allocation.
It needs to be called before reading from a mapped memory for memory types that are not `HOST_COHERENT`.
Map operation doesn't do that automatically.

- `offset` must be relative to the beginning of allocation.
- `size` can be `VK_WHOLE_SIZE`. It means all memory from `offset` the the end of given allocation.
- `offset` and `size` don't have to be aligned.
  They are internally rounded down/up to multiply of `nonCoherentAtomSize`.
- If `size` is 0, this call is ignored.
- If memory type that the `allocation` belongs to is not `HOST_VISIBLE` or it is `HOST_COHERENT`,
  this call is ignored.

Warning! `offset` and `size` are relative to the contents of given `allocation`.
If you mean whole allocation, you can pass 0 and `VK_WHOLE_SIZE`, respectively.
Do not pass allocation's offset as `offset`!!!

This function returns the `VkResult` from `vkInvalidateMappedMemoryRanges` if
it is called, otherwise `VK_SUCCESS`.
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaInvalidateAllocation(
    VmaAllocator VMA_NOT_NULL allocator,
    VmaAllocation VMA_NOT_NULL allocation,
    VkDeviceSize offset,
    VkDeviceSize size);

/** \brief Flushes memory of given set of allocations.

Calls `vkFlushMappedMemoryRanges()` for memory associated with given ranges of given allocations.
For more information, see documentation of vmaFlushAllocation().

\param allocator
\param allocationCount
\param allocations
\param offsets If not null, it must point to an array of offsets of regions to flush, relative to the beginning of respective allocations. Null means all ofsets are zero.
\param sizes If not null, it must point to an array of sizes of regions to flush in respective allocations. Null means `VK_WHOLE_SIZE` for all allocations.

This function returns the `VkResult` from `vkFlushMappedMemoryRanges` if it is
called, otherwise `VK_SUCCESS`.
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaFlushAllocations(
    VmaAllocator VMA_NOT_NULL allocator,
    uint32_t allocationCount,
    const VmaAllocation VMA_NOT_NULL * VMA_NULLABLE VMA_LEN_IF_NOT_NULL(allocationCount) allocations,
    const VkDeviceSize* VMA_NULLABLE VMA_LEN_IF_NOT_NULL(allocationCount) offsets,
    const VkDeviceSize* VMA_NULLABLE VMA_LEN_IF_NOT_NULL(allocationCount) sizes);

/** \brief Invalidates memory of given set of allocations.

Calls `vkInvalidateMappedMemoryRanges()` for memory associated with given ranges of given allocations.
For more information, see documentation of vmaInvalidateAllocation().

\param allocator
\param allocationCount
\param allocations
\param offsets If not null, it must point to an array of offsets of regions to flush, relative to the beginning of respective allocations. Null means all ofsets are zero.
\param sizes If not null, it must point to an array of sizes of regions to flush in respective allocations. Null means `VK_WHOLE_SIZE` for all allocations.

This function returns the `VkResult` from `vkInvalidateMappedMemoryRanges` if it is
called, otherwise `VK_SUCCESS`.
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaInvalidateAllocations(
    VmaAllocator VMA_NOT_NULL allocator,
    uint32_t allocationCount,
    const VmaAllocation VMA_NOT_NULL * VMA_NULLABLE VMA_LEN_IF_NOT_NULL(allocationCount) allocations,
    const VkDeviceSize* VMA_NULLABLE VMA_LEN_IF_NOT_NULL(allocationCount) offsets,
    const VkDeviceSize* VMA_NULLABLE VMA_LEN_IF_NOT_NULL(allocationCount) sizes);

/** \brief Checks magic number in margins around all allocations in given memory types (in both default and custom pools) in search for corruptions.

@param allocator
@param memoryTypeBits Bit mask, where each bit set means that a memory type with that index should be checked.

Corruption detection is enabled only when `VMA_DEBUG_DETECT_CORRUPTION` macro is defined to nonzero,
`VMA_DEBUG_MARGIN` is defined to nonzero and only for memory types that are
`HOST_VISIBLE` and `HOST_COHERENT`. For more information, see [Corruption detection](@ref debugging_memory_usage_corruption_detection).

Possible return values:

- `VK_ERROR_FEATURE_NOT_PRESENT` - corruption detection is not enabled for any of specified memory types.
- `VK_SUCCESS` - corruption detection has been performed and succeeded.
- `VK_ERROR_UNKNOWN` - corruption detection has been performed and found memory corruptions around one of the allocations.
  `VMA_ASSERT` is also fired in that case.
- Other value: Error returned by Vulkan, e.g. memory mapping failure.
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaCheckCorruption(VmaAllocator VMA_NOT_NULL allocator, uint32_t memoryTypeBits);

/** \struct VmaDefragmentationContext
\brief Represents Opaque object that represents started defragmentation process.

Fill structure #VmaDefragmentationInfo2 and call function vmaDefragmentationBegin() to create it.
Call function vmaDefragmentationEnd() to destroy it.
*/
VK_DEFINE_HANDLE(VmaDefragmentationContext)

/// Flags to be used in vmaDefragmentationBegin(). None at the moment. Reserved for future use.
typedef enum VmaDefragmentationFlagBits {
    VMA_DEFRAGMENTATION_FLAG_INCREMENTAL = 0x1,
    VMA_DEFRAGMENTATION_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
} VmaDefragmentationFlagBits;
typedef VkFlags VmaDefragmentationFlags;

/** \brief Parameters for defragmentation.

To be used with function vmaDefragmentationBegin().
*/
typedef struct VmaDefragmentationInfo2 {
    /** \brief Reserved for future use. Should be 0.
    */
    VmaDefragmentationFlags flags;
    /** \brief Number of allocations in `pAllocations` array.
    */
    uint32_t allocationCount;
    /** \brief Pointer to array of allocations that can be defragmented.

    The array should have `allocationCount` elements.
    The array should not contain nulls.
    Elements in the array should be unique - same allocation cannot occur twice.
    It is safe to pass allocations that are in the lost state - they are ignored.
    All allocations not present in this array are considered non-moveable during this defragmentation.
    */
    const VmaAllocation VMA_NOT_NULL * VMA_NULLABLE VMA_LEN_IF_NOT_NULL(allocationCount) pAllocations;
    /** \brief Optional, output. Pointer to array that will be filled with information whether the allocation at certain index has been changed during defragmentation.

    The array should have `allocationCount` elements.
    You can pass null if you are not interested in this information.
    */
    VkBool32* VMA_NULLABLE VMA_LEN_IF_NOT_NULL(allocationCount) pAllocationsChanged;
    /** \brief Numer of pools in `pPools` array.
    */
    uint32_t poolCount;
    /** \brief Either null or pointer to array of pools to be defragmented.

    All the allocations in the specified pools can be moved during defragmentation
    and there is no way to check if they were really moved as in `pAllocationsChanged`,
    so you must query all the allocations in all these pools for new `VkDeviceMemory`
    and offset using vmaGetAllocationInfo() if you might need to recreate buffers
    and images bound to them.

    The array should have `poolCount` elements.
    The array should not contain nulls.
    Elements in the array should be unique - same pool cannot occur twice.

    Using this array is equivalent to specifying all allocations from the pools in `pAllocations`.
    It might be more efficient.
    */
    const VmaPool VMA_NOT_NULL * VMA_NULLABLE VMA_LEN_IF_NOT_NULL(poolCount) pPools;
    /** \brief Maximum total numbers of bytes that can be copied while moving allocations to different places using transfers on CPU side, like `memcpy()`, `memmove()`.

    `VK_WHOLE_SIZE` means no limit.
    */
    VkDeviceSize maxCpuBytesToMove;
    /** \brief Maximum number of allocations that can be moved to a different place using transfers on CPU side, like `memcpy()`, `memmove()`.

    `UINT32_MAX` means no limit.
    */
    uint32_t maxCpuAllocationsToMove;
    /** \brief Maximum total numbers of bytes that can be copied while moving allocations to different places using transfers on GPU side, posted to `commandBuffer`.

    `VK_WHOLE_SIZE` means no limit.
    */
    VkDeviceSize maxGpuBytesToMove;
    /** \brief Maximum number of allocations that can be moved to a different place using transfers on GPU side, posted to `commandBuffer`.

    `UINT32_MAX` means no limit.
    */
    uint32_t maxGpuAllocationsToMove;
    /** \brief Optional. Command buffer where GPU copy commands will be posted.

    If not null, it must be a valid command buffer handle that supports Transfer queue type.
    It must be in the recording state and outside of a render pass instance.
    You need to submit it and make sure it finished execution before calling vmaDefragmentationEnd().

    Passing null means that only CPU defragmentation will be performed.
    */
    VkCommandBuffer VMA_NULLABLE commandBuffer;
} VmaDefragmentationInfo2;

typedef struct VmaDefragmentationPassMoveInfo {
    VmaAllocation VMA_NOT_NULL allocation;
    VkDeviceMemory VMA_NOT_NULL_NON_DISPATCHABLE memory;
    VkDeviceSize offset;
} VmaDefragmentationPassMoveInfo;

/** \brief Parameters for incremental defragmentation steps.

To be used with function vmaBeginDefragmentationPass().
*/
typedef struct VmaDefragmentationPassInfo {
    uint32_t moveCount;
    VmaDefragmentationPassMoveInfo* VMA_NOT_NULL VMA_LEN_IF_NOT_NULL(moveCount) pMoves;
} VmaDefragmentationPassInfo;

/** \brief Deprecated. Optional configuration parameters to be passed to function vmaDefragment().

\deprecated This is a part of the old interface. It is recommended to use structure #VmaDefragmentationInfo2 and function vmaDefragmentationBegin() instead.
*/
typedef struct VmaDefragmentationInfo {
    /** \brief Maximum total numbers of bytes that can be copied while moving allocations to different places.

    Default is `VK_WHOLE_SIZE`, which means no limit.
    */
    VkDeviceSize maxBytesToMove;
    /** \brief Maximum number of allocations that can be moved to different place.

    Default is `UINT32_MAX`, which means no limit.
    */
    uint32_t maxAllocationsToMove;
} VmaDefragmentationInfo;

/** \brief Statistics returned by function vmaDefragment(). */
typedef struct VmaDefragmentationStats {
    /// Total number of bytes that have been copied while moving allocations to different places.
    VkDeviceSize bytesMoved;
    /// Total number of bytes that have been released to the system by freeing empty `VkDeviceMemory` objects.
    VkDeviceSize bytesFreed;
    /// Number of allocations that have been moved to different places.
    uint32_t allocationsMoved;
    /// Number of empty `VkDeviceMemory` objects that have been released to the system.
    uint32_t deviceMemoryBlocksFreed;
} VmaDefragmentationStats;

/** \brief Begins defragmentation process.

@param allocator Allocator object.
@param pInfo Structure filled with parameters of defragmentation.
@param[out] pStats Optional. Statistics of defragmentation. You can pass null if you are not interested in this information.
@param[out] pContext Context object that must be passed to vmaDefragmentationEnd() to finish defragmentation.
@return `VK_SUCCESS` and `*pContext == null` if defragmentation finished within this function call. `VK_NOT_READY` and `*pContext != null` if defragmentation has been started and you need to call vmaDefragmentationEnd() to finish it. Negative value in case of error.

Use this function instead of old, deprecated vmaDefragment().

Warning! Between the call to vmaDefragmentationBegin() and vmaDefragmentationEnd():

- You should not use any of allocations passed as `pInfo->pAllocations` or
  any allocations that belong to pools passed as `pInfo->pPools`,
  including calling vmaGetAllocationInfo(), vmaTouchAllocation(), or access
  their data.
- Some mutexes protecting internal data structures may be locked, so trying to
  make or free any allocations, bind buffers or images, map memory, or launch
  another simultaneous defragmentation in between may cause stall (when done on
  another thread) or deadlock (when done on the same thread), unless you are
  100% sure that defragmented allocations are in different pools.
- Information returned via `pStats` and `pInfo->pAllocationsChanged` are undefined.
  They become valid after call to vmaDefragmentationEnd().
- If `pInfo->commandBuffer` is not null, you must submit that command buffer
  and make sure it finished execution before calling vmaDefragmentationEnd().

For more information and important limitations regarding defragmentation, see documentation chapter:
[Defragmentation](@ref defragmentation).
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaDefragmentationBegin(
    VmaAllocator VMA_NOT_NULL allocator,
    const VmaDefragmentationInfo2* VMA_NOT_NULL pInfo,
    VmaDefragmentationStats* VMA_NULLABLE pStats,
    VmaDefragmentationContext VMA_NULLABLE * VMA_NOT_NULL pContext);

/** \brief Ends defragmentation process.

Use this function to finish defragmentation started by vmaDefragmentationBegin().
It is safe to pass `context == null`. The function then does nothing.
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaDefragmentationEnd(
    VmaAllocator VMA_NOT_NULL allocator,
    VmaDefragmentationContext VMA_NULLABLE context);

VMA_CALL_PRE VkResult VMA_CALL_POST vmaBeginDefragmentationPass(
    VmaAllocator VMA_NOT_NULL allocator,
    VmaDefragmentationContext VMA_NULLABLE context,
    VmaDefragmentationPassInfo* VMA_NOT_NULL pInfo
);
VMA_CALL_PRE VkResult VMA_CALL_POST vmaEndDefragmentationPass(
    VmaAllocator VMA_NOT_NULL allocator,
    VmaDefragmentationContext VMA_NULLABLE context
);

/** \brief Deprecated. Compacts memory by moving allocations.

@param allocator
@param pAllocations Array of allocations that can be moved during this compation.
@param allocationCount Number of elements in pAllocations and pAllocationsChanged arrays.
@param[out] pAllocationsChanged Array of boolean values that will indicate whether matching allocation in pAllocations array has been moved. This parameter is optional. Pass null if you don't need this information.
@param pDefragmentationInfo Configuration parameters. Optional - pass null to use default values.
@param[out] pDefragmentationStats Statistics returned by the function. Optional - pass null if you don't need this information.
@return `VK_SUCCESS` if completed, negative error code in case of error.

\deprecated This is a part of the old interface. It is recommended to use structure #VmaDefragmentationInfo2 and function vmaDefragmentationBegin() instead.

This function works by moving allocations to different places (different
`VkDeviceMemory` objects and/or different offsets) in order to optimize memory
usage. Only allocations that are in `pAllocations` array can be moved. All other
allocations are considered nonmovable in this call. Basic rules:

- Only allocations made in memory types that have
  `VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT` and `VK_MEMORY_PROPERTY_HOST_COHERENT_BIT`
  flags can be compacted. You may pass other allocations but it makes no sense -
  these will never be moved.
- Custom pools created with #VMA_POOL_CREATE_LINEAR_ALGORITHM_BIT or
  #VMA_POOL_CREATE_BUDDY_ALGORITHM_BIT flag are not defragmented. Allocations
  passed to this function that come from such pools are ignored.
- Allocations created with #VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT or
  created as dedicated allocations for any other reason are also ignored.
- Both allocations made with or without #VMA_ALLOCATION_CREATE_MAPPED_BIT
  flag can be compacted. If not persistently mapped, memory will be mapped
  temporarily inside this function if needed.
- You must not pass same #VmaAllocation object multiple times in `pAllocations` array.

The function also frees empty `VkDeviceMemory` blocks.

Warning: This function may be time-consuming, so you shouldn't call it too often
(like after every resource creation/destruction).
You can call it on special occasions (like when reloading a game level or
when you just destroyed a lot of objects). Calling it every frame may be OK, but
you should measure that on your platform.

For more information, see [Defragmentation](@ref defragmentation) chapter.
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaDefragment(
    VmaAllocator VMA_NOT_NULL allocator,
    const VmaAllocation VMA_NOT_NULL * VMA_NOT_NULL VMA_LEN_IF_NOT_NULL(allocationCount) pAllocations,
    size_t allocationCount,
    VkBool32* VMA_NULLABLE VMA_LEN_IF_NOT_NULL(allocationCount) pAllocationsChanged,
    const VmaDefragmentationInfo* VMA_NULLABLE pDefragmentationInfo,
    VmaDefragmentationStats* VMA_NULLABLE pDefragmentationStats);

/** \brief Binds buffer to allocation.

Binds specified buffer to region of memory represented by specified allocation.
Gets `VkDeviceMemory` handle and offset from the allocation.
If you want to create a buffer, allocate memory for it and bind them together separately,
you should use this function for binding instead of standard `vkBindBufferMemory()`,
because it ensures proper synchronization so that when a `VkDeviceMemory` object is used by multiple
allocations, calls to `vkBind*Memory()` or `vkMapMemory()` won't happen from multiple threads simultaneously
(which is illegal in Vulkan).

It is recommended to use function vmaCreateBuffer() instead of this one.
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaBindBufferMemory(
    VmaAllocator VMA_NOT_NULL allocator,
    VmaAllocation VMA_NOT_NULL allocation,
    VkBuffer VMA_NOT_NULL_NON_DISPATCHABLE buffer);

/** \brief Binds buffer to allocation with additional parameters.

@param allocator
@param allocation
@param allocationLocalOffset Additional offset to be added while binding, relative to the beginning of the `allocation`. Normally it should be 0.
@param buffer
@param pNext A chain of structures to be attached to `VkBindBufferMemoryInfoKHR` structure used internally. Normally it should be null.

This function is similar to vmaBindBufferMemory(), but it provides additional parameters.

If `pNext` is not null, #VmaAllocator object must have been created with #VMA_ALLOCATOR_CREATE_KHR_BIND_MEMORY2_BIT flag
or with VmaAllocatorCreateInfo::vulkanApiVersion `>= VK_API_VERSION_1_1`. Otherwise the call fails.
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaBindBufferMemory2(
    VmaAllocator VMA_NOT_NULL allocator,
    VmaAllocation VMA_NOT_NULL allocation,
    VkDeviceSize allocationLocalOffset,
    VkBuffer VMA_NOT_NULL_NON_DISPATCHABLE buffer,
    const void* VMA_NULLABLE pNext);

/** \brief Binds image to allocation.

Binds specified image to region of memory represented by specified allocation.
Gets `VkDeviceMemory` handle and offset from the allocation.
If you want to create an image, allocate memory for it and bind them together separately,
you should use this function for binding instead of standard `vkBindImageMemory()`,
because it ensures proper synchronization so that when a `VkDeviceMemory` object is used by multiple
allocations, calls to `vkBind*Memory()` or `vkMapMemory()` won't happen from multiple threads simultaneously
(which is illegal in Vulkan).

It is recommended to use function vmaCreateImage() instead of this one.
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaBindImageMemory(
    VmaAllocator VMA_NOT_NULL allocator,
    VmaAllocation VMA_NOT_NULL allocation,
    VkImage VMA_NOT_NULL_NON_DISPATCHABLE image);

/** \brief Binds image to allocation with additional parameters.

@param allocator
@param allocation
@param allocationLocalOffset Additional offset to be added while binding, relative to the beginning of the `allocation`. Normally it should be 0.
@param image
@param pNext A chain of structures to be attached to `VkBindImageMemoryInfoKHR` structure used internally. Normally it should be null.

This function is similar to vmaBindImageMemory(), but it provides additional parameters.

If `pNext` is not null, #VmaAllocator object must have been created with #VMA_ALLOCATOR_CREATE_KHR_BIND_MEMORY2_BIT flag
or with VmaAllocatorCreateInfo::vulkanApiVersion `>= VK_API_VERSION_1_1`. Otherwise the call fails.
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaBindImageMemory2(
    VmaAllocator VMA_NOT_NULL allocator,
    VmaAllocation VMA_NOT_NULL allocation,
    VkDeviceSize allocationLocalOffset,
    VkImage VMA_NOT_NULL_NON_DISPATCHABLE image,
    const void* VMA_NULLABLE pNext);

/**
@param allocator
@param pBufferCreateInfo
@param pAllocationCreateInfo
@param[out] pBuffer Buffer that was created.
@param[out] pAllocation Allocation that was created.
@param[out] pAllocationInfo Optional. Information about allocated memory. It can be later fetched using function vmaGetAllocationInfo().

This function automatically:

-# Creates buffer.
-# Allocates appropriate memory for it.
-# Binds the buffer with the memory.

If any of these operations fail, buffer and allocation are not created,
returned value is negative error code, *pBuffer and *pAllocation are null.

If the function succeeded, you must destroy both buffer and allocation when you
no longer need them using either convenience function vmaDestroyBuffer() or
separately, using `vkDestroyBuffer()` and vmaFreeMemory().

If #VMA_ALLOCATOR_CREATE_KHR_DEDICATED_ALLOCATION_BIT flag was used,
VK_KHR_dedicated_allocation extension is used internally to query driver whether
it requires or prefers the new buffer to have dedicated allocation. If yes,
and if dedicated allocation is possible (VmaAllocationCreateInfo::pool is null
and #VMA_ALLOCATION_CREATE_NEVER_ALLOCATE_BIT is not used), it creates dedicated
allocation for this buffer, just like when using
#VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT.

\note This function creates a new `VkBuffer`. Sub-allocation of parts of one large buffer,
although recommended as a good practice, is out of scope of this library and could be implemented
by the user as a higher-level logic on top of VMA.
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaCreateBuffer(
    VmaAllocator VMA_NOT_NULL allocator,
    const VkBufferCreateInfo* VMA_NOT_NULL pBufferCreateInfo,
    const VmaAllocationCreateInfo* VMA_NOT_NULL pAllocationCreateInfo,
    VkBuffer VMA_NULLABLE_NON_DISPATCHABLE * VMA_NOT_NULL pBuffer,
    VmaAllocation VMA_NULLABLE * VMA_NOT_NULL pAllocation,
    VmaAllocationInfo* VMA_NULLABLE pAllocationInfo);

/** \brief Creates a buffer with additional minimum alignment.

Similar to vmaCreateBuffer() but provides additional parameter `minAlignment` which allows to specify custom,
minimum alignment to be used when placing the buffer inside a larger memory block, which may be needed e.g.
for interop with OpenGL.
*/
VMA_CALL_PRE VkResult VMA_CALL_POST vmaCreateBufferWithAlignment(
    VmaAllocator VMA_NOT_NULL allocator,
    const VkBufferCreateInfo* VMA_NOT_NULL pBufferCreateInfo,
    const VmaAllocationCreateInfo* VMA_NOT_NULL pAllocationCreateInfo,
    VkDeviceSize minAlignment,
    VkBuffer VMA_NULLABLE_NON_DISPATCHABLE * VMA_NOT_NULL pBuffer,
    VmaAllocation VMA_NULLABLE * VMA_NOT_NULL pAllocation,
    VmaAllocationInfo* VMA_NULLABLE pAllocationInfo);

/** \brief Destroys Vulkan buffer and frees allocated memory.

This is just a convenience function equivalent to:

\code
vkDestroyBuffer(device, buffer, allocationCallbacks);
vmaFreeMemory(allocator, allocation);
\endcode

It it safe to pass null as buffer and/or allocation.
*/
VMA_CALL_PRE void VMA_CALL_POST vmaDestroyBuffer(
    VmaAllocator VMA_NOT_NULL allocator,
    VkBuffer VMA_NULLABLE_NON_DISPATCHABLE buffer,
    VmaAllocation VMA_NULLABLE allocation);

/// Function similar to vmaCreateBuffer().
VMA_CALL_PRE VkResult VMA_CALL_POST vmaCreateImage(
    VmaAllocator VMA_NOT_NULL allocator,
    const VkImageCreateInfo* VMA_NOT_NULL pImageCreateInfo,
    const VmaAllocationCreateInfo* VMA_NOT_NULL pAllocationCreateInfo,
    VkImage VMA_NULLABLE_NON_DISPATCHABLE * VMA_NOT_NULL pImage,
    VmaAllocation VMA_NULLABLE * VMA_NOT_NULL pAllocation,
    VmaAllocationInfo* VMA_NULLABLE pAllocationInfo);

/** \brief Destroys Vulkan image and frees allocated memory.

This is just a convenience function equivalent to:

\code
vkDestroyImage(device, image, allocationCallbacks);
vmaFreeMemory(allocator, allocation);
\endcode

It it safe to pass null as image and/or allocation.
*/
VMA_CALL_PRE void VMA_CALL_POST vmaDestroyImage(
    VmaAllocator VMA_NOT_NULL allocator,
    VkImage VMA_NULLABLE_NON_DISPATCHABLE image,
    VmaAllocation VMA_NULLABLE allocation);

#ifdef __cplusplus
}
#endif

#endif // AMD_VULKAN_MEMORY_ALLOCATOR_H