package vma 

import c "core:c"
import vk "vendor:vulkan"

PFN_vmaAllocateDeviceMemoryFunction :: proc "stdcall" (allocator : Allocator, memoryType : u32, memory : vk.DeviceMemory, size : vk.DeviceSize, pUserData : rawptr)
PFN_vmaFreeDeviceMemoryFunction :: proc "stdcall" (allocator : Allocator, memoryType : u32, memory : vk.DeviceMemory, size : vk.DeviceSize, pUserData : rawptr)

foreign import VulkanMemoryAllocator "external/VulkanMemoryAllocator.lib"

foreign VulkanMemoryAllocator {
	vmaCreateAllocator                                                      :: proc(pCreateInfo : ^AllocatorCreateInfo, pAllocator : ^Allocator) -> vk.Result ---;
	vmaDestroyAllocator                                                     :: proc(allocator : Allocator) ---;
	vmaGetAllocatorInfo                                                     :: proc(allocator : Allocator, pAllocatorInfo : ^AllocatorInfo) ---;
	vmaGetPhysicalDeviceProperties                                          :: proc(allocator : Allocator, ppPhysicalDeviceProperties : ^^vk.PhysicalDeviceProperties) ---;
	vmaGetMemoryProperties                                                  :: proc(allocator : Allocator, ppPhysicalDeviceMemoryProperties : ^^vk.PhysicalDeviceMemoryProperties) ---;
	vmaGetMemoryTypeProperties                                              :: proc(allocator : Allocator, memoryTypeIndex : u32, pFlags : ^vk.MemoryPropertyFlags) ---;
	vmaSetCurrentFrameIndex                                                 :: proc(allocator : Allocator, frameIndex : u32) ---;
	vmaCalculateStats                                                       :: proc(allocator : Allocator, pStats : ^Stats) ---;
	vmaGetBudget                                                            :: proc(allocator : Allocator, pBudget : ^Budget) ---;
	vmaBuildStatsString                                                     :: proc(allocator : Allocator, ppStatsString : ^cstring, detailedMap : b32) ---;
	vmaFreeStatsString                                                      :: proc(allocator : Allocator, pStatsString : cstring) ---;
	vmaFindMemoryTypeIndex                                                  :: proc(allocator : Allocator, memoryTypeBits : u32, pAllocationCreateInfo : ^AllocationCreateInfo, pMemoryTypeIndex : ^u32) -> vk.Result ---;
	vmaFindMemoryTypeIndexForBufferInfo                                     :: proc(allocator : Allocator, pBufferCreateInfo : ^vk.BufferCreateInfo, pAllocationCreateInfo : ^AllocationCreateInfo, pMemoryTypeIndex : ^u32) -> vk.Result ---;
	vmaFindMemoryTypeIndexForImageInfo                                      :: proc(allocator : Allocator, pImageCreateInfo : ^vk.ImageCreateInfo, pAllocationCreateInfo : ^AllocationCreateInfo, pMemoryTypeIndex : ^u32) -> vk.Result ---;
	vmaCreatePool                                                           :: proc(allocator : Allocator, pCreateInfo : ^PoolCreateInfo, pPool : ^Pool) -> vk.Result ---;
	vmaDestroyPool                                                          :: proc(allocator : Allocator, pool : Pool) ---;
	vmaGetPoolStats                                                         :: proc(allocator : Allocator, pool : Pool, pPoolStats : ^PoolStats) ---;
	vmaMakePoolAllocationsLost                                              :: proc(allocator : Allocator, pool : Pool, pLostAllocationCount : ^uint) ---;
	vmaCheckPoolCorruption                                                  :: proc(allocator : Allocator, pool : Pool) -> vk.Result ---;
	vmaGetPoolName                                                          :: proc(allocator : Allocator, pool : Pool, ppName : ^cstring) ---;
	vmaSetPoolName                                                          :: proc(allocator : Allocator, pool : Pool, pName : cstring) ---;
	vmaAllocateMemory                                                       :: proc(allocator : Allocator, pVkMemoryRequirements : ^vk.MemoryRequirements, pCreateInfo : ^AllocationCreateInfo, pAllocation : ^Allocation, pAllocationInfo : ^AllocationInfo) -> vk.Result ---;
	vmaAllocateMemoryPages                                                  :: proc(allocator : Allocator, pVkMemoryRequirements : ^vk.MemoryRequirements, pCreateInfo : ^AllocationCreateInfo, allocationCount : uint, pAllocations : ^Allocation, pAllocationInfo : ^AllocationInfo) -> vk.Result ---;
	vmaAllocateMemoryForBuffer                                              :: proc(allocator : Allocator, buffer : vk.Buffer, pCreateInfo : ^AllocationCreateInfo, pAllocation : ^Allocation, pAllocationInfo : ^AllocationInfo) -> vk.Result ---;
	vmaAllocateMemoryForImage                                               :: proc(allocator : Allocator, image : vk.Image, pCreateInfo : ^AllocationCreateInfo, pAllocation : ^Allocation, pAllocationInfo : ^AllocationInfo) -> vk.Result ---;
	vmaFreeMemory                                                           :: proc(allocator : Allocator, allocation : Allocation) ---;
	vmaFreeMemoryPages                                                      :: proc(allocator : Allocator, allocationCount : uint, pAllocations : ^Allocation) ---;
	vmaGetAllocationInfo                                                    :: proc(allocator : Allocator, allocation : Allocation, pAllocationInfo : ^AllocationInfo) ---;
	vmaTouchAllocation                                                      :: proc(allocator : Allocator, allocation : Allocation) -> b32 ---;
	vmaSetAllocationUserData                                                :: proc(allocator : Allocator, allocation : Allocation, pUserData : rawptr) ---;
	vmaCreateLostAllocation                                                 :: proc(allocator : Allocator, pAllocation : ^Allocation) ---;
	vmaMapMemory                                                            :: proc(allocator : Allocator, allocation : Allocation, ppData : ^rawptr) -> vk.Result ---;
	vmaUnmapMemory                                                          :: proc(allocator : Allocator, allocation : Allocation) ---;
	vmaFlushAllocation                                                      :: proc(allocator : Allocator, allocation : Allocation, offset : vk.DeviceSize, size : vk.DeviceSize) -> vk.Result ---;
	vmaInvalidateAllocation                                                 :: proc(allocator : Allocator, allocation : Allocation, offset : vk.DeviceSize, size : vk.DeviceSize) -> vk.Result ---;
	vmaFlushAllocations                                                     :: proc(allocator : Allocator, allocationCount : u32, allocations : ^Allocation, offsets : ^vk.DeviceSize, sizes : ^vk.DeviceSize) -> vk.Result ---;
	vmaInvalidateAllocations                                                :: proc(allocator : Allocator, allocationCount : u32, allocations : ^Allocation, offsets : ^vk.DeviceSize, sizes : ^vk.DeviceSize) -> vk.Result ---;
	vmaCheckCorruption                                                      :: proc(allocator : Allocator, memoryTypeBits : u32) -> vk.Result ---;
	vmaDefragmentationBegin                                                 :: proc(allocator : Allocator, pInfo : ^DefragmentationInfo2, pStats : ^DefragmentationStats, pContext : ^DefragmentationContext) -> vk.Result ---;
	vmaDefragmentationEnd                                                   :: proc(allocator : Allocator, context_ : DefragmentationContext) -> vk.Result ---;
	vmaBeginDefragmentationPass                                             :: proc(allocator : Allocator, context_ : DefragmentationContext, pInfo : ^DefragmentationPassInfo) -> vk.Result ---;
	vmaEndDefragmentationPass                                               :: proc(allocator : Allocator, context_ : DefragmentationContext) -> vk.Result ---;
	vmaDefragment                                                           :: proc(allocator : Allocator, pAllocations : ^Allocation, allocationCount : uint, pAllocationsChanged : ^b32, pDefragmentationInfo : ^DefragmentationInfo, pDefragmentationStats : ^DefragmentationStats) -> vk.Result ---;
	vmaBindBufferMemory                                                     :: proc(allocator : Allocator, allocation : Allocation, buffer : vk.Buffer) -> vk.Result ---;
	vmaBindBufferMemory2                                                    :: proc(allocator : Allocator, allocation : Allocation, allocationLocalOffset : vk.DeviceSize, buffer : vk.Buffer, pNext : rawptr) -> vk.Result ---;
	vmaBindImageMemory                                                      :: proc(allocator : Allocator, allocation : Allocation, image : vk.Image) -> vk.Result ---;
	vmaBindImageMemory2                                                     :: proc(allocator : Allocator, allocation : Allocation, allocationLocalOffset : vk.DeviceSize, image : vk.Image, pNext : rawptr) -> vk.Result ---;
	vmaCreateBuffer                                                         :: proc(allocator : Allocator, pBufferCreateInfo : ^vk.BufferCreateInfo, pAllocationCreateInfo : ^AllocationCreateInfo, pBuffer : ^vk.Buffer, pAllocation : ^Allocation, pAllocationInfo : ^AllocationInfo) -> vk.Result ---;
	vmaCreateBufferWithAlignment                                            :: proc(allocator : Allocator, pBufferCreateInfo : ^vk.BufferCreateInfo, pAllocationCreateInfo : ^AllocationCreateInfo, minAlignment : vk.DeviceSize, pBuffer : ^vk.Buffer, pAllocation : ^Allocation, pAllocationInfo : ^AllocationInfo) -> vk.Result ---;
	vmaDestroyBuffer                                                        :: proc(allocator : Allocator, buffer : vk.Buffer, allocation : Allocation) ---;
	vmaCreateImage                                                          :: proc(allocator : Allocator, pImageCreateInfo : ^vk.ImageCreateInfo, pAllocationCreateInfo : ^AllocationCreateInfo, pImage : ^vk.Image, pAllocation : ^Allocation, pAllocationInfo : ^AllocationInfo) -> vk.Result ---;
	vmaDestroyImage                                                         :: proc(allocator : Allocator, image : vk.Image, allocation : Allocation) ---;
}


