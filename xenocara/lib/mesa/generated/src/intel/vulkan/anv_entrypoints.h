
/* Copyright © 2015-2021 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
/* This file generated from vk_entrypoints_gen.py, don't edit directly. */

#include "vk_dispatch_table.h"


#ifndef ANV_ENTRYPOINTS_H
#define ANV_ENTRYPOINTS_H

#ifdef __cplusplus
extern "C" {
#endif

/* clang wants function declarations in the header to have weak attribute */
#if !defined(_MSC_VER) && !defined(__MINGW32__)
#define ATTR_WEAK __attribute__ ((weak))
#else
#define ATTR_WEAK
#endif

extern const struct vk_instance_entrypoint_table anv_instance_entrypoints;

extern const struct vk_physical_device_entrypoint_table anv_physical_device_entrypoints;

extern const struct vk_device_entrypoint_table anv_device_entrypoints;
extern const struct vk_device_entrypoint_table gfx9_device_entrypoints;
extern const struct vk_device_entrypoint_table gfx11_device_entrypoints;
extern const struct vk_device_entrypoint_table gfx12_device_entrypoints;
extern const struct vk_device_entrypoint_table gfx125_device_entrypoints;
extern const struct vk_device_entrypoint_table doom64_device_entrypoints;
extern const struct vk_device_entrypoint_table hitman3_device_entrypoints;
extern const struct vk_device_entrypoint_table android_device_entrypoints;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateInstance(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance);
  VKAPI_ATTR void VKAPI_CALL anv_DestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator);
  VKAPI_ATTR VkResult VKAPI_CALL anv_EnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices);
  VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL anv_GetInstanceProcAddr(VkInstance instance, const char* pName);
  VKAPI_ATTR VkResult VKAPI_CALL anv_EnumerateInstanceVersion(uint32_t* pApiVersion);
  VKAPI_ATTR VkResult VKAPI_CALL anv_EnumerateInstanceLayerProperties(uint32_t* pPropertyCount, VkLayerProperties* pProperties);
  VKAPI_ATTR VkResult VKAPI_CALL anv_EnumerateInstanceExtensionProperties(const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties);
#ifdef VK_USE_PLATFORM_ANDROID_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateAndroidSurfaceKHR(VkInstance instance, const VkAndroidSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
#endif // VK_USE_PLATFORM_ANDROID_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateDisplayPlaneSurfaceKHR(VkInstance instance, const VkDisplaySurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
  VKAPI_ATTR void VKAPI_CALL anv_DestroySurfaceKHR(VkInstance instance, VkSurfaceKHR surface, const VkAllocationCallbacks* pAllocator);
#ifdef VK_USE_PLATFORM_VI_NN
  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateViSurfaceNN(VkInstance instance, const VkViSurfaceCreateInfoNN* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
#endif // VK_USE_PLATFORM_VI_NN
#ifdef VK_USE_PLATFORM_WAYLAND_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateWaylandSurfaceKHR(VkInstance instance, const VkWaylandSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
#endif // VK_USE_PLATFORM_WAYLAND_KHR
#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateWin32SurfaceKHR(VkInstance instance, const VkWin32SurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
#endif // VK_USE_PLATFORM_WIN32_KHR
#ifdef VK_USE_PLATFORM_XLIB_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateXlibSurfaceKHR(VkInstance instance, const VkXlibSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
#endif // VK_USE_PLATFORM_XLIB_KHR
#ifdef VK_USE_PLATFORM_XCB_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateXcbSurfaceKHR(VkInstance instance, const VkXcbSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
#endif // VK_USE_PLATFORM_XCB_KHR
#ifdef VK_USE_PLATFORM_DIRECTFB_EXT
  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateDirectFBSurfaceEXT(VkInstance instance, const VkDirectFBSurfaceCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
#endif // VK_USE_PLATFORM_DIRECTFB_EXT
#ifdef VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateImagePipeSurfaceFUCHSIA(VkInstance instance, const VkImagePipeSurfaceCreateInfoFUCHSIA* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
#endif // VK_USE_PLATFORM_FUCHSIA
#ifdef VK_USE_PLATFORM_GGP
  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateStreamDescriptorSurfaceGGP(VkInstance instance, const VkStreamDescriptorSurfaceCreateInfoGGP* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
#endif // VK_USE_PLATFORM_GGP
#ifdef VK_USE_PLATFORM_SCREEN_QNX
  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateScreenSurfaceQNX(VkInstance instance, const VkScreenSurfaceCreateInfoQNX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
#endif // VK_USE_PLATFORM_SCREEN_QNX
  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);
  VKAPI_ATTR void VKAPI_CALL anv_DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);
  VKAPI_ATTR void VKAPI_CALL anv_DebugReportMessageEXT(VkInstance instance, VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage);
  VKAPI_ATTR VkResult VKAPI_CALL anv_EnumeratePhysicalDeviceGroups(VkInstance instance, uint32_t* pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties);
  VKAPI_ATTR VkResult VKAPI_CALL anv_EnumeratePhysicalDeviceGroupsKHR(VkInstance instance, uint32_t* pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties);
#ifdef VK_USE_PLATFORM_IOS_MVK
  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateIOSSurfaceMVK(VkInstance instance, const VkIOSSurfaceCreateInfoMVK* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
#endif // VK_USE_PLATFORM_IOS_MVK
#ifdef VK_USE_PLATFORM_MACOS_MVK
  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateMacOSSurfaceMVK(VkInstance instance, const VkMacOSSurfaceCreateInfoMVK* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
#endif // VK_USE_PLATFORM_MACOS_MVK
#ifdef VK_USE_PLATFORM_METAL_EXT
  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateMetalSurfaceEXT(VkInstance instance, const VkMetalSurfaceCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
#endif // VK_USE_PLATFORM_METAL_EXT
  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pMessenger);
  VKAPI_ATTR void VKAPI_CALL anv_DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT messenger, const VkAllocationCallbacks* pAllocator);
  VKAPI_ATTR void VKAPI_CALL anv_SubmitDebugUtilsMessageEXT(VkInstance instance, VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData);
  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateHeadlessSurfaceEXT(VkInstance instance, const VkHeadlessSurfaceCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties* pMemoryProperties);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties* pFormatProperties);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties* pImageFormatProperties);
  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice);
  VKAPI_ATTR VkResult VKAPI_CALL anv_EnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkLayerProperties* pProperties);
  VKAPI_ATTR VkResult VKAPI_CALL anv_EnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceSparseImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, uint32_t* pPropertyCount, VkSparseImageFormatProperties* pProperties);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceDisplayPropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPropertiesKHR* pProperties);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceDisplayPlanePropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPlanePropertiesKHR* pProperties);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetDisplayPlaneSupportedDisplaysKHR(VkPhysicalDevice physicalDevice, uint32_t planeIndex, uint32_t* pDisplayCount, VkDisplayKHR* pDisplays);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetDisplayModePropertiesKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t* pPropertyCount, VkDisplayModePropertiesKHR* pProperties);
  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateDisplayModeKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, const VkDisplayModeCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDisplayModeKHR* pMode);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetDisplayPlaneCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkDisplayModeKHR mode, uint32_t planeIndex, VkDisplayPlaneCapabilitiesKHR* pCapabilities);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, VkSurfaceKHR surface, VkBool32* pSupported);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceSurfaceCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR* pSurfaceCapabilities);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pSurfaceFormatCount, VkSurfaceFormatKHR* pSurfaceFormats);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceSurfacePresentModesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes);
#ifdef VK_USE_PLATFORM_WAYLAND_KHR
  VKAPI_ATTR VkBool32 VKAPI_CALL anv_GetPhysicalDeviceWaylandPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, struct wl_display* display);
#endif // VK_USE_PLATFORM_WAYLAND_KHR
#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkBool32 VKAPI_CALL anv_GetPhysicalDeviceWin32PresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex);
#endif // VK_USE_PLATFORM_WIN32_KHR
#ifdef VK_USE_PLATFORM_XLIB_KHR
  VKAPI_ATTR VkBool32 VKAPI_CALL anv_GetPhysicalDeviceXlibPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, Display* dpy, VisualID visualID);
#endif // VK_USE_PLATFORM_XLIB_KHR
#ifdef VK_USE_PLATFORM_XCB_KHR
  VKAPI_ATTR VkBool32 VKAPI_CALL anv_GetPhysicalDeviceXcbPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, xcb_connection_t* connection, xcb_visualid_t visual_id);
#endif // VK_USE_PLATFORM_XCB_KHR
#ifdef VK_USE_PLATFORM_DIRECTFB_EXT
  VKAPI_ATTR VkBool32 VKAPI_CALL anv_GetPhysicalDeviceDirectFBPresentationSupportEXT(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, IDirectFB* dfb);
#endif // VK_USE_PLATFORM_DIRECTFB_EXT
#ifdef VK_USE_PLATFORM_SCREEN_QNX
  VKAPI_ATTR VkBool32 VKAPI_CALL anv_GetPhysicalDeviceScreenPresentationSupportQNX(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, struct _screen_window* window);
#endif // VK_USE_PLATFORM_SCREEN_QNX
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceExternalImageFormatPropertiesNV(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkExternalMemoryHandleTypeFlagsNV externalHandleType, VkExternalImageFormatPropertiesNV* pExternalImageFormatProperties);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceFeatures2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2* pFeatures);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceFeatures2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2* pFeatures);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2* pProperties);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2* pProperties);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceFormatProperties2(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2* pFormatProperties);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceFormatProperties2KHR(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2* pFormatProperties);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceImageFormatProperties2(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo, VkImageFormatProperties2* pImageFormatProperties);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceImageFormatProperties2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo, VkImageFormatProperties2* pImageFormatProperties);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceQueueFamilyProperties2(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties2* pQueueFamilyProperties);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceQueueFamilyProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties2* pQueueFamilyProperties);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceMemoryProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2* pMemoryProperties);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceMemoryProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2* pMemoryProperties);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceSparseImageFormatProperties2(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo, uint32_t* pPropertyCount, VkSparseImageFormatProperties2* pProperties);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceSparseImageFormatProperties2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo, uint32_t* pPropertyCount, VkSparseImageFormatProperties2* pProperties);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceExternalBufferProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo, VkExternalBufferProperties* pExternalBufferProperties);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceExternalBufferPropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo, VkExternalBufferProperties* pExternalBufferProperties);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceExternalSemaphoreProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo, VkExternalSemaphoreProperties* pExternalSemaphoreProperties);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceExternalSemaphorePropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo, VkExternalSemaphoreProperties* pExternalSemaphoreProperties);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceExternalFenceProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo, VkExternalFenceProperties* pExternalFenceProperties);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceExternalFencePropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo, VkExternalFenceProperties* pExternalFenceProperties);
  VKAPI_ATTR VkResult VKAPI_CALL anv_ReleaseDisplayEXT(VkPhysicalDevice physicalDevice, VkDisplayKHR display);
#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
  VKAPI_ATTR VkResult VKAPI_CALL anv_AcquireXlibDisplayEXT(VkPhysicalDevice physicalDevice, Display* dpy, VkDisplayKHR display);
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT
#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetRandROutputDisplayEXT(VkPhysicalDevice physicalDevice, Display* dpy, RROutput rrOutput, VkDisplayKHR* pDisplay);
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT
#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_AcquireWinrtDisplayNV(VkPhysicalDevice physicalDevice, VkDisplayKHR display);
#endif // VK_USE_PLATFORM_WIN32_KHR
#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetWinrtDisplayNV(VkPhysicalDevice physicalDevice, uint32_t deviceRelativeId, VkDisplayKHR* pDisplay);
#endif // VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceSurfaceCapabilities2EXT(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilities2EXT* pSurfaceCapabilities);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDevicePresentRectanglesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pRectCount, VkRect2D* pRects);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceMultisamplePropertiesEXT(VkPhysicalDevice physicalDevice, VkSampleCountFlagBits samples, VkMultisamplePropertiesEXT* pMultisampleProperties);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceSurfaceCapabilities2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkSurfaceCapabilities2KHR* pSurfaceCapabilities);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceSurfaceFormats2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* pSurfaceFormatCount, VkSurfaceFormat2KHR* pSurfaceFormats);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceDisplayProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayProperties2KHR* pProperties);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceDisplayPlaneProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPlaneProperties2KHR* pProperties);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetDisplayModeProperties2KHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t* pPropertyCount, VkDisplayModeProperties2KHR* pProperties);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetDisplayPlaneCapabilities2KHR(VkPhysicalDevice physicalDevice, const VkDisplayPlaneInfo2KHR* pDisplayPlaneInfo, VkDisplayPlaneCapabilities2KHR* pCapabilities);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceCalibrateableTimeDomainsEXT(VkPhysicalDevice physicalDevice, uint32_t* pTimeDomainCount, VkTimeDomainEXT* pTimeDomains);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceCooperativeMatrixPropertiesNV(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkCooperativeMatrixPropertiesNV* pProperties);
#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceSurfacePresentModes2EXT(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes);
#endif // VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, uint32_t* pCounterCount, VkPerformanceCounterKHR* pCounters, VkPerformanceCounterDescriptionKHR* pCounterDescriptions);
  VKAPI_ATTR void VKAPI_CALL anv_GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(VkPhysicalDevice physicalDevice, const VkQueryPoolPerformanceCreateInfoKHR* pPerformanceQueryCreateInfo, uint32_t* pNumPasses);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(VkPhysicalDevice physicalDevice, uint32_t* pCombinationCount, VkFramebufferMixedSamplesCombinationNV* pCombinations);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceToolProperties(VkPhysicalDevice physicalDevice, uint32_t* pToolCount, VkPhysicalDeviceToolProperties* pToolProperties);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceToolPropertiesEXT(VkPhysicalDevice physicalDevice, uint32_t* pToolCount, VkPhysicalDeviceToolProperties* pToolProperties);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceFragmentShadingRatesKHR(VkPhysicalDevice physicalDevice, uint32_t* pFragmentShadingRateCount, VkPhysicalDeviceFragmentShadingRateKHR* pFragmentShadingRates);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceVideoCapabilitiesKHR(VkPhysicalDevice physicalDevice, const VkVideoProfileInfoKHR* pVideoProfile, VkVideoCapabilitiesKHR* pCapabilities);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceVideoFormatPropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceVideoFormatInfoKHR* pVideoFormatInfo, uint32_t* pVideoFormatPropertyCount, VkVideoFormatPropertiesKHR* pVideoFormatProperties);
  VKAPI_ATTR VkResult VKAPI_CALL anv_AcquireDrmDisplayEXT(VkPhysicalDevice physicalDevice, int32_t drmFd, VkDisplayKHR display);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetDrmDisplayEXT(VkPhysicalDevice physicalDevice, int32_t drmFd, uint32_t connectorId, VkDisplayKHR* display);
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPhysicalDeviceOpticalFlowImageFormatsNV(VkPhysicalDevice physicalDevice, const VkOpticalFlowImageFormatInfoNV* pOpticalFlowImageFormatInfo, uint32_t* pFormatCount, VkOpticalFlowImageFormatPropertiesNV* pImageFormatProperties);

  VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL anv_GetDeviceProcAddr(VkDevice device, const char* pName) ATTR_WEAK;
  VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL gfx9_GetDeviceProcAddr(VkDevice device, const char* pName) ATTR_WEAK;
  VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL gfx11_GetDeviceProcAddr(VkDevice device, const char* pName) ATTR_WEAK;
  VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL gfx12_GetDeviceProcAddr(VkDevice device, const char* pName) ATTR_WEAK;
  VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL gfx125_GetDeviceProcAddr(VkDevice device, const char* pName) ATTR_WEAK;
  VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL doom64_GetDeviceProcAddr(VkDevice device, const char* pName) ATTR_WEAK;
  VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL hitman3_GetDeviceProcAddr(VkDevice device, const char* pName) ATTR_WEAK;
  VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL android_GetDeviceProcAddr(VkDevice device, const char* pName) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_QueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_QueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_QueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_QueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_QueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_QueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_QueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_QueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_QueueWaitIdle(VkQueue queue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_QueueWaitIdle(VkQueue queue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_QueueWaitIdle(VkQueue queue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_QueueWaitIdle(VkQueue queue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_QueueWaitIdle(VkQueue queue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_QueueWaitIdle(VkQueue queue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_QueueWaitIdle(VkQueue queue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_QueueWaitIdle(VkQueue queue) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_DeviceWaitIdle(VkDevice device) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_DeviceWaitIdle(VkDevice device) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_DeviceWaitIdle(VkDevice device) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_DeviceWaitIdle(VkDevice device) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_DeviceWaitIdle(VkDevice device) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_DeviceWaitIdle(VkDevice device) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_DeviceWaitIdle(VkDevice device) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_DeviceWaitIdle(VkDevice device) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_AllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_AllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_AllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_AllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_AllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_AllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_AllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_AllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_FreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_FreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_FreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_FreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_FreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_FreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_FreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_FreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_MapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_MapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_MapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_MapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_MapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_MapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_MapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_MapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_UnmapMemory(VkDevice device, VkDeviceMemory memory) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_UnmapMemory(VkDevice device, VkDeviceMemory memory) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_UnmapMemory(VkDevice device, VkDeviceMemory memory) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_UnmapMemory(VkDevice device, VkDeviceMemory memory) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_UnmapMemory(VkDevice device, VkDeviceMemory memory) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_UnmapMemory(VkDevice device, VkDeviceMemory memory) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_UnmapMemory(VkDevice device, VkDeviceMemory memory) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_UnmapMemory(VkDevice device, VkDeviceMemory memory) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_FlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_FlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_FlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_FlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_FlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_FlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_FlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_FlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_InvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_InvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_InvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_InvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_InvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_InvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_InvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_InvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize* pCommittedMemoryInBytes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize* pCommittedMemoryInBytes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize* pCommittedMemoryInBytes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize* pCommittedMemoryInBytes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize* pCommittedMemoryInBytes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize* pCommittedMemoryInBytes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize* pCommittedMemoryInBytes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize* pCommittedMemoryInBytes) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_BindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_BindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_BindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_BindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_BindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_BindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_BindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_BindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_BindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_BindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_BindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_BindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_BindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_BindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_BindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_BindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_QueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo* pBindInfo, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_QueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo* pBindInfo, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_QueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo* pBindInfo, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_QueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo* pBindInfo, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_QueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo* pBindInfo, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_QueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo* pBindInfo, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_QueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo* pBindInfo, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_QueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo* pBindInfo, VkFence fence) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_ResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_ResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_ResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_ResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_ResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_ResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_ResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_ResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetFenceStatus(VkDevice device, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetFenceStatus(VkDevice device, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetFenceStatus(VkDevice device, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetFenceStatus(VkDevice device, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetFenceStatus(VkDevice device, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetFenceStatus(VkDevice device, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetFenceStatus(VkDevice device, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetFenceStatus(VkDevice device, VkFence fence) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_WaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_WaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_WaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_WaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_WaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_WaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_WaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_WaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateEvent(VkDevice device, const VkEventCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkEvent* pEvent) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateEvent(VkDevice device, const VkEventCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkEvent* pEvent) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateEvent(VkDevice device, const VkEventCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkEvent* pEvent) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateEvent(VkDevice device, const VkEventCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkEvent* pEvent) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateEvent(VkDevice device, const VkEventCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkEvent* pEvent) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateEvent(VkDevice device, const VkEventCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkEvent* pEvent) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateEvent(VkDevice device, const VkEventCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkEvent* pEvent) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateEvent(VkDevice device, const VkEventCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkEvent* pEvent) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetEventStatus(VkDevice device, VkEvent event) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetEventStatus(VkDevice device, VkEvent event) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetEventStatus(VkDevice device, VkEvent event) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetEventStatus(VkDevice device, VkEvent event) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetEventStatus(VkDevice device, VkEvent event) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetEventStatus(VkDevice device, VkEvent event) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetEventStatus(VkDevice device, VkEvent event) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetEventStatus(VkDevice device, VkEvent event) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_SetEvent(VkDevice device, VkEvent event) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_SetEvent(VkDevice device, VkEvent event) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_SetEvent(VkDevice device, VkEvent event) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_SetEvent(VkDevice device, VkEvent event) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_SetEvent(VkDevice device, VkEvent event) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_SetEvent(VkDevice device, VkEvent event) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_SetEvent(VkDevice device, VkEvent event) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_SetEvent(VkDevice device, VkEvent event) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_ResetEvent(VkDevice device, VkEvent event) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_ResetEvent(VkDevice device, VkEvent event) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_ResetEvent(VkDevice device, VkEvent event) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_ResetEvent(VkDevice device, VkEvent event) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_ResetEvent(VkDevice device, VkEvent event) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_ResetEvent(VkDevice device, VkEvent event) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_ResetEvent(VkDevice device, VkEvent event) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_ResetEvent(VkDevice device, VkEvent event) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyQueryPool(VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyQueryPool(VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyQueryPool(VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyQueryPool(VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyQueryPool(VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyQueryPool(VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyQueryPool(VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyQueryPool(VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void* pData, VkDeviceSize stride, VkQueryResultFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void* pData, VkDeviceSize stride, VkQueryResultFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void* pData, VkDeviceSize stride, VkQueryResultFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void* pData, VkDeviceSize stride, VkQueryResultFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void* pData, VkDeviceSize stride, VkQueryResultFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void* pData, VkDeviceSize stride, VkQueryResultFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void* pData, VkDeviceSize stride, VkQueryResultFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void* pData, VkDeviceSize stride, VkQueryResultFlags flags) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_ResetQueryPool(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_ResetQueryPool(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_ResetQueryPool(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_ResetQueryPool(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_ResetQueryPool(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_ResetQueryPool(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_ResetQueryPool(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_ResetQueryPool(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_ResetQueryPoolEXT(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_ResetQueryPoolEXT(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_ResetQueryPoolEXT(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_ResetQueryPoolEXT(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_ResetQueryPoolEXT(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_ResetQueryPoolEXT(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_ResetQueryPoolEXT(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_ResetQueryPoolEXT(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateBufferView(VkDevice device, const VkBufferViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferView* pView) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateBufferView(VkDevice device, const VkBufferViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferView* pView) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateBufferView(VkDevice device, const VkBufferViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferView* pView) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateBufferView(VkDevice device, const VkBufferViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferView* pView) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateBufferView(VkDevice device, const VkBufferViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferView* pView) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateBufferView(VkDevice device, const VkBufferViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferView* pView) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateBufferView(VkDevice device, const VkBufferViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferView* pView) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateBufferView(VkDevice device, const VkBufferViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferView* pView) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyShaderModule(VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyShaderModule(VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyShaderModule(VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyShaderModule(VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyShaderModule(VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyShaderModule(VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyShaderModule(VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyShaderModule(VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t* pDataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t* pDataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t* pDataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t* pDataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t* pDataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t* pDataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t* pDataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t* pDataSize, void* pData) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_MergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, const VkPipelineCache* pSrcCaches) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_MergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, const VkPipelineCache* pSrcCaches) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_MergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, const VkPipelineCache* pSrcCaches) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_MergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, const VkPipelineCache* pSrcCaches) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_MergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, const VkPipelineCache* pSrcCaches) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_MergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, const VkPipelineCache* pSrcCaches) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_MergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, const VkPipelineCache* pSrcCaches) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_MergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, const VkPipelineCache* pSrcCaches) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI(VkDevice device, VkRenderPass renderpass, VkExtent2D* pMaxWorkgroupSize) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI(VkDevice device, VkRenderPass renderpass, VkExtent2D* pMaxWorkgroupSize) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI(VkDevice device, VkRenderPass renderpass, VkExtent2D* pMaxWorkgroupSize) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI(VkDevice device, VkRenderPass renderpass, VkExtent2D* pMaxWorkgroupSize) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI(VkDevice device, VkRenderPass renderpass, VkExtent2D* pMaxWorkgroupSize) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI(VkDevice device, VkRenderPass renderpass, VkExtent2D* pMaxWorkgroupSize) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI(VkDevice device, VkRenderPass renderpass, VkExtent2D* pMaxWorkgroupSize) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI(VkDevice device, VkRenderPass renderpass, VkExtent2D* pMaxWorkgroupSize) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyPipeline(VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyPipeline(VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyPipeline(VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyPipeline(VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyPipeline(VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyPipeline(VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyPipeline(VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyPipeline(VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateSampler(VkDevice device, const VkSamplerCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateSampler(VkDevice device, const VkSamplerCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateSampler(VkDevice device, const VkSamplerCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateSampler(VkDevice device, const VkSamplerCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateSampler(VkDevice device, const VkSamplerCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateSampler(VkDevice device, const VkSamplerCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateSampler(VkDevice device, const VkSamplerCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateSampler(VkDevice device, const VkSamplerCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* pSetLayout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* pSetLayout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* pSetLayout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* pSetLayout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* pSetLayout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* pSetLayout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* pSetLayout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* pSetLayout) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_ResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_ResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_ResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_ResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_ResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_ResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_ResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_ResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_AllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_AllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_AllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_AllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_AllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_AllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_AllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_AllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_FreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_FreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_FreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_FreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_FreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_FreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_FreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_FreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_UpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_UpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_UpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_UpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_UpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_UpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_UpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_UpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D* pGranularity) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D* pGranularity) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D* pGranularity) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D* pGranularity) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D* pGranularity) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D* pGranularity) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D* pGranularity) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D* pGranularity) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_ResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_ResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_ResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_ResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_ResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_ResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_ResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_ResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_AllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_AllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_AllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_AllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_AllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_AllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_AllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_AllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_FreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_FreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_FreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_FreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_FreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_FreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_FreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_FreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_BeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_BeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_BeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_BeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_BeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_BeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_BeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_BeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_EndCommandBuffer(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_EndCommandBuffer(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_EndCommandBuffer(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_EndCommandBuffer(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_EndCommandBuffer(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_EndCommandBuffer(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_EndCommandBuffer(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_EndCommandBuffer(VkCommandBuffer commandBuffer) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_ResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_ResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_ResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_ResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_ResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_ResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_ResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_ResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants[4]) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants[4]) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants[4]) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants[4]) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants[4]) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants[4]) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants[4]) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants[4]) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDrawMultiEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawInfoEXT* pVertexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDrawMultiEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawInfoEXT* pVertexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDrawMultiEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawInfoEXT* pVertexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDrawMultiEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawInfoEXT* pVertexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDrawMultiEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawInfoEXT* pVertexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDrawMultiEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawInfoEXT* pVertexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDrawMultiEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawInfoEXT* pVertexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDrawMultiEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawInfoEXT* pVertexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDrawMultiIndexedEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawIndexedInfoEXT* pIndexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride, const int32_t* pVertexOffset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDrawMultiIndexedEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawIndexedInfoEXT* pIndexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride, const int32_t* pVertexOffset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDrawMultiIndexedEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawIndexedInfoEXT* pIndexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride, const int32_t* pVertexOffset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDrawMultiIndexedEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawIndexedInfoEXT* pIndexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride, const int32_t* pVertexOffset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDrawMultiIndexedEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawIndexedInfoEXT* pIndexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride, const int32_t* pVertexOffset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDrawMultiIndexedEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawIndexedInfoEXT* pIndexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride, const int32_t* pVertexOffset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDrawMultiIndexedEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawIndexedInfoEXT* pIndexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride, const int32_t* pVertexOffset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDrawMultiIndexedEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawIndexedInfoEXT* pIndexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride, const int32_t* pVertexOffset) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSubpassShadingHUAWEI(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSubpassShadingHUAWEI(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSubpassShadingHUAWEI(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSubpassShadingHUAWEI(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSubpassShadingHUAWEI(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSubpassShadingHUAWEI(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSubpassShadingHUAWEI(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSubpassShadingHUAWEI(VkCommandBuffer commandBuffer) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDrawClusterHUAWEI(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDrawClusterHUAWEI(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDrawClusterHUAWEI(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDrawClusterHUAWEI(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDrawClusterHUAWEI(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDrawClusterHUAWEI(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDrawClusterHUAWEI(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDrawClusterHUAWEI(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDrawClusterIndirectHUAWEI(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDrawClusterIndirectHUAWEI(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDrawClusterIndirectHUAWEI(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDrawClusterIndirectHUAWEI(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDrawClusterIndirectHUAWEI(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDrawClusterIndirectHUAWEI(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDrawClusterIndirectHUAWEI(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDrawClusterIndirectHUAWEI(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy* pRegions) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit* pRegions, VkFilter filter) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit* pRegions, VkFilter filter) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit* pRegions, VkFilter filter) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit* pRegions, VkFilter filter) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit* pRegions, VkFilter filter) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit* pRegions, VkFilter filter) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit* pRegions, VkFilter filter) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit* pRegions, VkFilter filter) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCopyMemoryIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCopyMemoryIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCopyMemoryIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCopyMemoryIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCopyMemoryIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCopyMemoryIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCopyMemoryIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCopyMemoryIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCopyMemoryToImageIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride, VkImage dstImage, VkImageLayout dstImageLayout, const VkImageSubresourceLayers* pImageSubresources) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCopyMemoryToImageIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride, VkImage dstImage, VkImageLayout dstImageLayout, const VkImageSubresourceLayers* pImageSubresources) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCopyMemoryToImageIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride, VkImage dstImage, VkImageLayout dstImageLayout, const VkImageSubresourceLayers* pImageSubresources) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCopyMemoryToImageIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride, VkImage dstImage, VkImageLayout dstImageLayout, const VkImageSubresourceLayers* pImageSubresources) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCopyMemoryToImageIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride, VkImage dstImage, VkImageLayout dstImageLayout, const VkImageSubresourceLayers* pImageSubresources) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCopyMemoryToImageIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride, VkImage dstImage, VkImageLayout dstImageLayout, const VkImageSubresourceLayers* pImageSubresources) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCopyMemoryToImageIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride, VkImage dstImage, VkImageLayout dstImageLayout, const VkImageSubresourceLayers* pImageSubresources) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCopyMemoryToImageIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride, VkImage dstImage, VkImageLayout dstImageLayout, const VkImageSubresourceLayers* pImageSubresources) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void* pData) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue* pColor, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue* pColor, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue* pColor, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue* pColor, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue* pColor, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue* pColor, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue* pColor, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue* pColor, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* pRects) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* pRects) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* pRects) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* pRects) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* pRects) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* pRects) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* pRects) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* pRects) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve* pRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve* pRegions) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBeginConditionalRenderingEXT(VkCommandBuffer commandBuffer, const VkConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBeginConditionalRenderingEXT(VkCommandBuffer commandBuffer, const VkConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBeginConditionalRenderingEXT(VkCommandBuffer commandBuffer, const VkConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBeginConditionalRenderingEXT(VkCommandBuffer commandBuffer, const VkConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBeginConditionalRenderingEXT(VkCommandBuffer commandBuffer, const VkConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBeginConditionalRenderingEXT(VkCommandBuffer commandBuffer, const VkConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBeginConditionalRenderingEXT(VkCommandBuffer commandBuffer, const VkConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBeginConditionalRenderingEXT(VkCommandBuffer commandBuffer, const VkConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdEndConditionalRenderingEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdEndConditionalRenderingEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdEndConditionalRenderingEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdEndConditionalRenderingEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdEndConditionalRenderingEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdEndConditionalRenderingEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdEndConditionalRenderingEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdEndConditionalRenderingEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdEndRenderPass(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdEndRenderPass(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdEndRenderPass(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdEndRenderPass(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdEndRenderPass(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdEndRenderPass(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdEndRenderPass(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdEndRenderPass(VkCommandBuffer commandBuffer) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateSharedSwapchainsKHR(VkDevice device, uint32_t swapchainCount, const VkSwapchainCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchains) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateSharedSwapchainsKHR(VkDevice device, uint32_t swapchainCount, const VkSwapchainCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchains) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateSharedSwapchainsKHR(VkDevice device, uint32_t swapchainCount, const VkSwapchainCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchains) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateSharedSwapchainsKHR(VkDevice device, uint32_t swapchainCount, const VkSwapchainCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchains) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateSharedSwapchainsKHR(VkDevice device, uint32_t swapchainCount, const VkSwapchainCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchains) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateSharedSwapchainsKHR(VkDevice device, uint32_t swapchainCount, const VkSwapchainCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchains) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateSharedSwapchainsKHR(VkDevice device, uint32_t swapchainCount, const VkSwapchainCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchains) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateSharedSwapchainsKHR(VkDevice device, uint32_t swapchainCount, const VkSwapchainCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchains) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_AcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_AcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_AcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_AcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_AcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_AcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_AcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_AcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_QueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_QueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_QueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_QueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_QueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_QueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_QueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_QueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_DebugMarkerSetObjectNameEXT(VkDevice device, const VkDebugMarkerObjectNameInfoEXT* pNameInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_DebugMarkerSetObjectNameEXT(VkDevice device, const VkDebugMarkerObjectNameInfoEXT* pNameInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_DebugMarkerSetObjectNameEXT(VkDevice device, const VkDebugMarkerObjectNameInfoEXT* pNameInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_DebugMarkerSetObjectNameEXT(VkDevice device, const VkDebugMarkerObjectNameInfoEXT* pNameInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_DebugMarkerSetObjectNameEXT(VkDevice device, const VkDebugMarkerObjectNameInfoEXT* pNameInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_DebugMarkerSetObjectNameEXT(VkDevice device, const VkDebugMarkerObjectNameInfoEXT* pNameInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_DebugMarkerSetObjectNameEXT(VkDevice device, const VkDebugMarkerObjectNameInfoEXT* pNameInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_DebugMarkerSetObjectNameEXT(VkDevice device, const VkDebugMarkerObjectNameInfoEXT* pNameInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_DebugMarkerSetObjectTagEXT(VkDevice device, const VkDebugMarkerObjectTagInfoEXT* pTagInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_DebugMarkerSetObjectTagEXT(VkDevice device, const VkDebugMarkerObjectTagInfoEXT* pTagInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_DebugMarkerSetObjectTagEXT(VkDevice device, const VkDebugMarkerObjectTagInfoEXT* pTagInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_DebugMarkerSetObjectTagEXT(VkDevice device, const VkDebugMarkerObjectTagInfoEXT* pTagInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_DebugMarkerSetObjectTagEXT(VkDevice device, const VkDebugMarkerObjectTagInfoEXT* pTagInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_DebugMarkerSetObjectTagEXT(VkDevice device, const VkDebugMarkerObjectTagInfoEXT* pTagInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_DebugMarkerSetObjectTagEXT(VkDevice device, const VkDebugMarkerObjectTagInfoEXT* pTagInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_DebugMarkerSetObjectTagEXT(VkDevice device, const VkDebugMarkerObjectTagInfoEXT* pTagInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDebugMarkerBeginEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDebugMarkerBeginEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDebugMarkerBeginEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDebugMarkerBeginEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDebugMarkerBeginEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDebugMarkerBeginEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDebugMarkerBeginEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDebugMarkerBeginEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDebugMarkerEndEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDebugMarkerEndEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDebugMarkerEndEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDebugMarkerEndEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDebugMarkerEndEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDebugMarkerEndEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDebugMarkerEndEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDebugMarkerEndEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDebugMarkerInsertEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDebugMarkerInsertEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDebugMarkerInsertEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDebugMarkerInsertEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDebugMarkerInsertEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDebugMarkerInsertEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDebugMarkerInsertEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDebugMarkerInsertEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) ATTR_WEAK;


#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetMemoryWin32HandleNV(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetMemoryWin32HandleNV(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetMemoryWin32HandleNV(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetMemoryWin32HandleNV(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetMemoryWin32HandleNV(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetMemoryWin32HandleNV(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetMemoryWin32HandleNV(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetMemoryWin32HandleNV(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle) ATTR_WEAK;


#endif // VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR void VKAPI_CALL anv_CmdExecuteGeneratedCommandsNV(VkCommandBuffer commandBuffer, VkBool32 isPreprocessed, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdExecuteGeneratedCommandsNV(VkCommandBuffer commandBuffer, VkBool32 isPreprocessed, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdExecuteGeneratedCommandsNV(VkCommandBuffer commandBuffer, VkBool32 isPreprocessed, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdExecuteGeneratedCommandsNV(VkCommandBuffer commandBuffer, VkBool32 isPreprocessed, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdExecuteGeneratedCommandsNV(VkCommandBuffer commandBuffer, VkBool32 isPreprocessed, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdExecuteGeneratedCommandsNV(VkCommandBuffer commandBuffer, VkBool32 isPreprocessed, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdExecuteGeneratedCommandsNV(VkCommandBuffer commandBuffer, VkBool32 isPreprocessed, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdExecuteGeneratedCommandsNV(VkCommandBuffer commandBuffer, VkBool32 isPreprocessed, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdPreprocessGeneratedCommandsNV(VkCommandBuffer commandBuffer, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdPreprocessGeneratedCommandsNV(VkCommandBuffer commandBuffer, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdPreprocessGeneratedCommandsNV(VkCommandBuffer commandBuffer, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdPreprocessGeneratedCommandsNV(VkCommandBuffer commandBuffer, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdPreprocessGeneratedCommandsNV(VkCommandBuffer commandBuffer, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdPreprocessGeneratedCommandsNV(VkCommandBuffer commandBuffer, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdPreprocessGeneratedCommandsNV(VkCommandBuffer commandBuffer, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdPreprocessGeneratedCommandsNV(VkCommandBuffer commandBuffer, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBindPipelineShaderGroupNV(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline, uint32_t groupIndex) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBindPipelineShaderGroupNV(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline, uint32_t groupIndex) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBindPipelineShaderGroupNV(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline, uint32_t groupIndex) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBindPipelineShaderGroupNV(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline, uint32_t groupIndex) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBindPipelineShaderGroupNV(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline, uint32_t groupIndex) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBindPipelineShaderGroupNV(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline, uint32_t groupIndex) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBindPipelineShaderGroupNV(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline, uint32_t groupIndex) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBindPipelineShaderGroupNV(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline, uint32_t groupIndex) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetGeneratedCommandsMemoryRequirementsNV(VkDevice device, const VkGeneratedCommandsMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetGeneratedCommandsMemoryRequirementsNV(VkDevice device, const VkGeneratedCommandsMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetGeneratedCommandsMemoryRequirementsNV(VkDevice device, const VkGeneratedCommandsMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetGeneratedCommandsMemoryRequirementsNV(VkDevice device, const VkGeneratedCommandsMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetGeneratedCommandsMemoryRequirementsNV(VkDevice device, const VkGeneratedCommandsMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetGeneratedCommandsMemoryRequirementsNV(VkDevice device, const VkGeneratedCommandsMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetGeneratedCommandsMemoryRequirementsNV(VkDevice device, const VkGeneratedCommandsMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetGeneratedCommandsMemoryRequirementsNV(VkDevice device, const VkGeneratedCommandsMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateIndirectCommandsLayoutNV(VkDevice device, const VkIndirectCommandsLayoutCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectCommandsLayoutNV* pIndirectCommandsLayout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateIndirectCommandsLayoutNV(VkDevice device, const VkIndirectCommandsLayoutCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectCommandsLayoutNV* pIndirectCommandsLayout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateIndirectCommandsLayoutNV(VkDevice device, const VkIndirectCommandsLayoutCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectCommandsLayoutNV* pIndirectCommandsLayout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateIndirectCommandsLayoutNV(VkDevice device, const VkIndirectCommandsLayoutCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectCommandsLayoutNV* pIndirectCommandsLayout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateIndirectCommandsLayoutNV(VkDevice device, const VkIndirectCommandsLayoutCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectCommandsLayoutNV* pIndirectCommandsLayout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateIndirectCommandsLayoutNV(VkDevice device, const VkIndirectCommandsLayoutCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectCommandsLayoutNV* pIndirectCommandsLayout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateIndirectCommandsLayoutNV(VkDevice device, const VkIndirectCommandsLayoutCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectCommandsLayoutNV* pIndirectCommandsLayout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateIndirectCommandsLayoutNV(VkDevice device, const VkIndirectCommandsLayoutCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectCommandsLayoutNV* pIndirectCommandsLayout) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyIndirectCommandsLayoutNV(VkDevice device, VkIndirectCommandsLayoutNV indirectCommandsLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyIndirectCommandsLayoutNV(VkDevice device, VkIndirectCommandsLayoutNV indirectCommandsLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyIndirectCommandsLayoutNV(VkDevice device, VkIndirectCommandsLayoutNV indirectCommandsLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyIndirectCommandsLayoutNV(VkDevice device, VkIndirectCommandsLayoutNV indirectCommandsLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyIndirectCommandsLayoutNV(VkDevice device, VkIndirectCommandsLayoutNV indirectCommandsLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyIndirectCommandsLayoutNV(VkDevice device, VkIndirectCommandsLayoutNV indirectCommandsLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyIndirectCommandsLayoutNV(VkDevice device, VkIndirectCommandsLayoutNV indirectCommandsLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyIndirectCommandsLayoutNV(VkDevice device, VkIndirectCommandsLayoutNV indirectCommandsLayout, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdPushDescriptorSetKHR(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdPushDescriptorSetKHR(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdPushDescriptorSetKHR(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdPushDescriptorSetKHR(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdPushDescriptorSetKHR(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdPushDescriptorSetKHR(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdPushDescriptorSetKHR(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdPushDescriptorSetKHR(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_TrimCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_TrimCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_TrimCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_TrimCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_TrimCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_TrimCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_TrimCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_TrimCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_TrimCommandPoolKHR(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_TrimCommandPoolKHR(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_TrimCommandPoolKHR(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_TrimCommandPoolKHR(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_TrimCommandPoolKHR(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_TrimCommandPoolKHR(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_TrimCommandPoolKHR(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_TrimCommandPoolKHR(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) ATTR_WEAK;


#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetMemoryWin32HandleKHR(VkDevice device, const VkMemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetMemoryWin32HandleKHR(VkDevice device, const VkMemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetMemoryWin32HandleKHR(VkDevice device, const VkMemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetMemoryWin32HandleKHR(VkDevice device, const VkMemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetMemoryWin32HandleKHR(VkDevice device, const VkMemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetMemoryWin32HandleKHR(VkDevice device, const VkMemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetMemoryWin32HandleKHR(VkDevice device, const VkMemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetMemoryWin32HandleKHR(VkDevice device, const VkMemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;


#endif // VK_USE_PLATFORM_WIN32_KHR
#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetMemoryWin32HandlePropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetMemoryWin32HandlePropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetMemoryWin32HandlePropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetMemoryWin32HandlePropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetMemoryWin32HandlePropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetMemoryWin32HandlePropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetMemoryWin32HandlePropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetMemoryWin32HandlePropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties) ATTR_WEAK;


#endif // VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetMemoryFdKHR(VkDevice device, const VkMemoryGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetMemoryFdKHR(VkDevice device, const VkMemoryGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetMemoryFdKHR(VkDevice device, const VkMemoryGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetMemoryFdKHR(VkDevice device, const VkMemoryGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetMemoryFdKHR(VkDevice device, const VkMemoryGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetMemoryFdKHR(VkDevice device, const VkMemoryGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetMemoryFdKHR(VkDevice device, const VkMemoryGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetMemoryFdKHR(VkDevice device, const VkMemoryGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetMemoryFdPropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, int fd, VkMemoryFdPropertiesKHR* pMemoryFdProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetMemoryFdPropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, int fd, VkMemoryFdPropertiesKHR* pMemoryFdProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetMemoryFdPropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, int fd, VkMemoryFdPropertiesKHR* pMemoryFdProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetMemoryFdPropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, int fd, VkMemoryFdPropertiesKHR* pMemoryFdProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetMemoryFdPropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, int fd, VkMemoryFdPropertiesKHR* pMemoryFdProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetMemoryFdPropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, int fd, VkMemoryFdPropertiesKHR* pMemoryFdProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetMemoryFdPropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, int fd, VkMemoryFdPropertiesKHR* pMemoryFdProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetMemoryFdPropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, int fd, VkMemoryFdPropertiesKHR* pMemoryFdProperties) ATTR_WEAK;


#ifdef VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetMemoryZirconHandleFUCHSIA(VkDevice device, const VkMemoryGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetMemoryZirconHandleFUCHSIA(VkDevice device, const VkMemoryGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetMemoryZirconHandleFUCHSIA(VkDevice device, const VkMemoryGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetMemoryZirconHandleFUCHSIA(VkDevice device, const VkMemoryGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetMemoryZirconHandleFUCHSIA(VkDevice device, const VkMemoryGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetMemoryZirconHandleFUCHSIA(VkDevice device, const VkMemoryGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetMemoryZirconHandleFUCHSIA(VkDevice device, const VkMemoryGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetMemoryZirconHandleFUCHSIA(VkDevice device, const VkMemoryGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle) ATTR_WEAK;


#endif // VK_USE_PLATFORM_FUCHSIA
#ifdef VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetMemoryZirconHandlePropertiesFUCHSIA(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, zx_handle_t zirconHandle, VkMemoryZirconHandlePropertiesFUCHSIA* pMemoryZirconHandleProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetMemoryZirconHandlePropertiesFUCHSIA(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, zx_handle_t zirconHandle, VkMemoryZirconHandlePropertiesFUCHSIA* pMemoryZirconHandleProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetMemoryZirconHandlePropertiesFUCHSIA(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, zx_handle_t zirconHandle, VkMemoryZirconHandlePropertiesFUCHSIA* pMemoryZirconHandleProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetMemoryZirconHandlePropertiesFUCHSIA(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, zx_handle_t zirconHandle, VkMemoryZirconHandlePropertiesFUCHSIA* pMemoryZirconHandleProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetMemoryZirconHandlePropertiesFUCHSIA(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, zx_handle_t zirconHandle, VkMemoryZirconHandlePropertiesFUCHSIA* pMemoryZirconHandleProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetMemoryZirconHandlePropertiesFUCHSIA(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, zx_handle_t zirconHandle, VkMemoryZirconHandlePropertiesFUCHSIA* pMemoryZirconHandleProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetMemoryZirconHandlePropertiesFUCHSIA(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, zx_handle_t zirconHandle, VkMemoryZirconHandlePropertiesFUCHSIA* pMemoryZirconHandleProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetMemoryZirconHandlePropertiesFUCHSIA(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, zx_handle_t zirconHandle, VkMemoryZirconHandlePropertiesFUCHSIA* pMemoryZirconHandleProperties) ATTR_WEAK;


#endif // VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetMemoryRemoteAddressNV(VkDevice device, const VkMemoryGetRemoteAddressInfoNV* pMemoryGetRemoteAddressInfo, VkRemoteAddressNV* pAddress) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetMemoryRemoteAddressNV(VkDevice device, const VkMemoryGetRemoteAddressInfoNV* pMemoryGetRemoteAddressInfo, VkRemoteAddressNV* pAddress) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetMemoryRemoteAddressNV(VkDevice device, const VkMemoryGetRemoteAddressInfoNV* pMemoryGetRemoteAddressInfo, VkRemoteAddressNV* pAddress) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetMemoryRemoteAddressNV(VkDevice device, const VkMemoryGetRemoteAddressInfoNV* pMemoryGetRemoteAddressInfo, VkRemoteAddressNV* pAddress) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetMemoryRemoteAddressNV(VkDevice device, const VkMemoryGetRemoteAddressInfoNV* pMemoryGetRemoteAddressInfo, VkRemoteAddressNV* pAddress) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetMemoryRemoteAddressNV(VkDevice device, const VkMemoryGetRemoteAddressInfoNV* pMemoryGetRemoteAddressInfo, VkRemoteAddressNV* pAddress) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetMemoryRemoteAddressNV(VkDevice device, const VkMemoryGetRemoteAddressInfoNV* pMemoryGetRemoteAddressInfo, VkRemoteAddressNV* pAddress) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetMemoryRemoteAddressNV(VkDevice device, const VkMemoryGetRemoteAddressInfoNV* pMemoryGetRemoteAddressInfo, VkRemoteAddressNV* pAddress) ATTR_WEAK;


#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetSemaphoreWin32HandleKHR(VkDevice device, const VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetSemaphoreWin32HandleKHR(VkDevice device, const VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetSemaphoreWin32HandleKHR(VkDevice device, const VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetSemaphoreWin32HandleKHR(VkDevice device, const VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetSemaphoreWin32HandleKHR(VkDevice device, const VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetSemaphoreWin32HandleKHR(VkDevice device, const VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetSemaphoreWin32HandleKHR(VkDevice device, const VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetSemaphoreWin32HandleKHR(VkDevice device, const VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;


#endif // VK_USE_PLATFORM_WIN32_KHR
#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_ImportSemaphoreWin32HandleKHR(VkDevice device, const VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_ImportSemaphoreWin32HandleKHR(VkDevice device, const VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_ImportSemaphoreWin32HandleKHR(VkDevice device, const VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_ImportSemaphoreWin32HandleKHR(VkDevice device, const VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_ImportSemaphoreWin32HandleKHR(VkDevice device, const VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_ImportSemaphoreWin32HandleKHR(VkDevice device, const VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_ImportSemaphoreWin32HandleKHR(VkDevice device, const VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_ImportSemaphoreWin32HandleKHR(VkDevice device, const VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo) ATTR_WEAK;


#endif // VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetSemaphoreFdKHR(VkDevice device, const VkSemaphoreGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetSemaphoreFdKHR(VkDevice device, const VkSemaphoreGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetSemaphoreFdKHR(VkDevice device, const VkSemaphoreGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetSemaphoreFdKHR(VkDevice device, const VkSemaphoreGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetSemaphoreFdKHR(VkDevice device, const VkSemaphoreGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetSemaphoreFdKHR(VkDevice device, const VkSemaphoreGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetSemaphoreFdKHR(VkDevice device, const VkSemaphoreGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetSemaphoreFdKHR(VkDevice device, const VkSemaphoreGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_ImportSemaphoreFdKHR(VkDevice device, const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_ImportSemaphoreFdKHR(VkDevice device, const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_ImportSemaphoreFdKHR(VkDevice device, const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_ImportSemaphoreFdKHR(VkDevice device, const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_ImportSemaphoreFdKHR(VkDevice device, const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_ImportSemaphoreFdKHR(VkDevice device, const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_ImportSemaphoreFdKHR(VkDevice device, const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_ImportSemaphoreFdKHR(VkDevice device, const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo) ATTR_WEAK;


#ifdef VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetSemaphoreZirconHandleFUCHSIA(VkDevice device, const VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetSemaphoreZirconHandleFUCHSIA(VkDevice device, const VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetSemaphoreZirconHandleFUCHSIA(VkDevice device, const VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetSemaphoreZirconHandleFUCHSIA(VkDevice device, const VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetSemaphoreZirconHandleFUCHSIA(VkDevice device, const VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetSemaphoreZirconHandleFUCHSIA(VkDevice device, const VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetSemaphoreZirconHandleFUCHSIA(VkDevice device, const VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetSemaphoreZirconHandleFUCHSIA(VkDevice device, const VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle) ATTR_WEAK;


#endif // VK_USE_PLATFORM_FUCHSIA
#ifdef VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR VkResult VKAPI_CALL anv_ImportSemaphoreZirconHandleFUCHSIA(VkDevice device, const VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_ImportSemaphoreZirconHandleFUCHSIA(VkDevice device, const VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_ImportSemaphoreZirconHandleFUCHSIA(VkDevice device, const VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_ImportSemaphoreZirconHandleFUCHSIA(VkDevice device, const VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_ImportSemaphoreZirconHandleFUCHSIA(VkDevice device, const VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_ImportSemaphoreZirconHandleFUCHSIA(VkDevice device, const VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_ImportSemaphoreZirconHandleFUCHSIA(VkDevice device, const VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_ImportSemaphoreZirconHandleFUCHSIA(VkDevice device, const VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo) ATTR_WEAK;


#endif // VK_USE_PLATFORM_FUCHSIA
#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetFenceWin32HandleKHR(VkDevice device, const VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetFenceWin32HandleKHR(VkDevice device, const VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetFenceWin32HandleKHR(VkDevice device, const VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetFenceWin32HandleKHR(VkDevice device, const VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetFenceWin32HandleKHR(VkDevice device, const VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetFenceWin32HandleKHR(VkDevice device, const VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetFenceWin32HandleKHR(VkDevice device, const VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetFenceWin32HandleKHR(VkDevice device, const VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) ATTR_WEAK;


#endif // VK_USE_PLATFORM_WIN32_KHR
#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_ImportFenceWin32HandleKHR(VkDevice device, const VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_ImportFenceWin32HandleKHR(VkDevice device, const VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_ImportFenceWin32HandleKHR(VkDevice device, const VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_ImportFenceWin32HandleKHR(VkDevice device, const VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_ImportFenceWin32HandleKHR(VkDevice device, const VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_ImportFenceWin32HandleKHR(VkDevice device, const VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_ImportFenceWin32HandleKHR(VkDevice device, const VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_ImportFenceWin32HandleKHR(VkDevice device, const VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo) ATTR_WEAK;


#endif // VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetFenceFdKHR(VkDevice device, const VkFenceGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetFenceFdKHR(VkDevice device, const VkFenceGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetFenceFdKHR(VkDevice device, const VkFenceGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetFenceFdKHR(VkDevice device, const VkFenceGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetFenceFdKHR(VkDevice device, const VkFenceGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetFenceFdKHR(VkDevice device, const VkFenceGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetFenceFdKHR(VkDevice device, const VkFenceGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetFenceFdKHR(VkDevice device, const VkFenceGetFdInfoKHR* pGetFdInfo, int* pFd) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_ImportFenceFdKHR(VkDevice device, const VkImportFenceFdInfoKHR* pImportFenceFdInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_ImportFenceFdKHR(VkDevice device, const VkImportFenceFdInfoKHR* pImportFenceFdInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_ImportFenceFdKHR(VkDevice device, const VkImportFenceFdInfoKHR* pImportFenceFdInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_ImportFenceFdKHR(VkDevice device, const VkImportFenceFdInfoKHR* pImportFenceFdInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_ImportFenceFdKHR(VkDevice device, const VkImportFenceFdInfoKHR* pImportFenceFdInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_ImportFenceFdKHR(VkDevice device, const VkImportFenceFdInfoKHR* pImportFenceFdInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_ImportFenceFdKHR(VkDevice device, const VkImportFenceFdInfoKHR* pImportFenceFdInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_ImportFenceFdKHR(VkDevice device, const VkImportFenceFdInfoKHR* pImportFenceFdInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_DisplayPowerControlEXT(VkDevice device, VkDisplayKHR display, const VkDisplayPowerInfoEXT* pDisplayPowerInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_DisplayPowerControlEXT(VkDevice device, VkDisplayKHR display, const VkDisplayPowerInfoEXT* pDisplayPowerInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_DisplayPowerControlEXT(VkDevice device, VkDisplayKHR display, const VkDisplayPowerInfoEXT* pDisplayPowerInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_DisplayPowerControlEXT(VkDevice device, VkDisplayKHR display, const VkDisplayPowerInfoEXT* pDisplayPowerInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_DisplayPowerControlEXT(VkDevice device, VkDisplayKHR display, const VkDisplayPowerInfoEXT* pDisplayPowerInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_DisplayPowerControlEXT(VkDevice device, VkDisplayKHR display, const VkDisplayPowerInfoEXT* pDisplayPowerInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_DisplayPowerControlEXT(VkDevice device, VkDisplayKHR display, const VkDisplayPowerInfoEXT* pDisplayPowerInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_DisplayPowerControlEXT(VkDevice device, VkDisplayKHR display, const VkDisplayPowerInfoEXT* pDisplayPowerInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_RegisterDeviceEventEXT(VkDevice device, const VkDeviceEventInfoEXT* pDeviceEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_RegisterDeviceEventEXT(VkDevice device, const VkDeviceEventInfoEXT* pDeviceEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_RegisterDeviceEventEXT(VkDevice device, const VkDeviceEventInfoEXT* pDeviceEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_RegisterDeviceEventEXT(VkDevice device, const VkDeviceEventInfoEXT* pDeviceEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_RegisterDeviceEventEXT(VkDevice device, const VkDeviceEventInfoEXT* pDeviceEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_RegisterDeviceEventEXT(VkDevice device, const VkDeviceEventInfoEXT* pDeviceEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_RegisterDeviceEventEXT(VkDevice device, const VkDeviceEventInfoEXT* pDeviceEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_RegisterDeviceEventEXT(VkDevice device, const VkDeviceEventInfoEXT* pDeviceEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_RegisterDisplayEventEXT(VkDevice device, VkDisplayKHR display, const VkDisplayEventInfoEXT* pDisplayEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_RegisterDisplayEventEXT(VkDevice device, VkDisplayKHR display, const VkDisplayEventInfoEXT* pDisplayEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_RegisterDisplayEventEXT(VkDevice device, VkDisplayKHR display, const VkDisplayEventInfoEXT* pDisplayEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_RegisterDisplayEventEXT(VkDevice device, VkDisplayKHR display, const VkDisplayEventInfoEXT* pDisplayEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_RegisterDisplayEventEXT(VkDevice device, VkDisplayKHR display, const VkDisplayEventInfoEXT* pDisplayEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_RegisterDisplayEventEXT(VkDevice device, VkDisplayKHR display, const VkDisplayEventInfoEXT* pDisplayEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_RegisterDisplayEventEXT(VkDevice device, VkDisplayKHR display, const VkDisplayEventInfoEXT* pDisplayEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_RegisterDisplayEventEXT(VkDevice device, VkDisplayKHR display, const VkDisplayEventInfoEXT* pDisplayEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetSwapchainCounterEXT(VkDevice device, VkSwapchainKHR swapchain, VkSurfaceCounterFlagBitsEXT counter, uint64_t* pCounterValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetSwapchainCounterEXT(VkDevice device, VkSwapchainKHR swapchain, VkSurfaceCounterFlagBitsEXT counter, uint64_t* pCounterValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetSwapchainCounterEXT(VkDevice device, VkSwapchainKHR swapchain, VkSurfaceCounterFlagBitsEXT counter, uint64_t* pCounterValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetSwapchainCounterEXT(VkDevice device, VkSwapchainKHR swapchain, VkSurfaceCounterFlagBitsEXT counter, uint64_t* pCounterValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetSwapchainCounterEXT(VkDevice device, VkSwapchainKHR swapchain, VkSurfaceCounterFlagBitsEXT counter, uint64_t* pCounterValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetSwapchainCounterEXT(VkDevice device, VkSwapchainKHR swapchain, VkSurfaceCounterFlagBitsEXT counter, uint64_t* pCounterValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetSwapchainCounterEXT(VkDevice device, VkSwapchainKHR swapchain, VkSurfaceCounterFlagBitsEXT counter, uint64_t* pCounterValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetSwapchainCounterEXT(VkDevice device, VkSwapchainKHR swapchain, VkSurfaceCounterFlagBitsEXT counter, uint64_t* pCounterValue) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetDeviceGroupPeerMemoryFeatures(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetDeviceGroupPeerMemoryFeatures(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetDeviceGroupPeerMemoryFeatures(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetDeviceGroupPeerMemoryFeatures(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetDeviceGroupPeerMemoryFeatures(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetDeviceGroupPeerMemoryFeatures(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetDeviceGroupPeerMemoryFeatures(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetDeviceGroupPeerMemoryFeatures(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetDeviceGroupPeerMemoryFeaturesKHR(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetDeviceGroupPeerMemoryFeaturesKHR(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetDeviceGroupPeerMemoryFeaturesKHR(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetDeviceGroupPeerMemoryFeaturesKHR(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetDeviceGroupPeerMemoryFeaturesKHR(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetDeviceGroupPeerMemoryFeaturesKHR(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetDeviceGroupPeerMemoryFeaturesKHR(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetDeviceGroupPeerMemoryFeaturesKHR(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_BindBufferMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_BindBufferMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_BindBufferMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_BindBufferMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_BindBufferMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_BindBufferMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_BindBufferMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_BindBufferMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_BindBufferMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_BindBufferMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_BindBufferMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_BindBufferMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_BindBufferMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_BindBufferMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_BindBufferMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_BindBufferMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_BindImageMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_BindImageMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_BindImageMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_BindImageMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_BindImageMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_BindImageMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_BindImageMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_BindImageMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_BindImageMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_BindImageMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_BindImageMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_BindImageMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_BindImageMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_BindImageMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_BindImageMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_BindImageMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetDeviceMask(VkCommandBuffer commandBuffer, uint32_t deviceMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetDeviceMask(VkCommandBuffer commandBuffer, uint32_t deviceMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetDeviceMask(VkCommandBuffer commandBuffer, uint32_t deviceMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetDeviceMask(VkCommandBuffer commandBuffer, uint32_t deviceMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetDeviceMask(VkCommandBuffer commandBuffer, uint32_t deviceMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetDeviceMask(VkCommandBuffer commandBuffer, uint32_t deviceMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetDeviceMask(VkCommandBuffer commandBuffer, uint32_t deviceMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetDeviceMask(VkCommandBuffer commandBuffer, uint32_t deviceMask) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetDeviceMaskKHR(VkCommandBuffer commandBuffer, uint32_t deviceMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetDeviceMaskKHR(VkCommandBuffer commandBuffer, uint32_t deviceMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetDeviceMaskKHR(VkCommandBuffer commandBuffer, uint32_t deviceMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetDeviceMaskKHR(VkCommandBuffer commandBuffer, uint32_t deviceMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetDeviceMaskKHR(VkCommandBuffer commandBuffer, uint32_t deviceMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetDeviceMaskKHR(VkCommandBuffer commandBuffer, uint32_t deviceMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetDeviceMaskKHR(VkCommandBuffer commandBuffer, uint32_t deviceMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetDeviceMaskKHR(VkCommandBuffer commandBuffer, uint32_t deviceMask) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetDeviceGroupPresentCapabilitiesKHR(VkDevice device, VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetDeviceGroupPresentCapabilitiesKHR(VkDevice device, VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetDeviceGroupPresentCapabilitiesKHR(VkDevice device, VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetDeviceGroupPresentCapabilitiesKHR(VkDevice device, VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetDeviceGroupPresentCapabilitiesKHR(VkDevice device, VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetDeviceGroupPresentCapabilitiesKHR(VkDevice device, VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetDeviceGroupPresentCapabilitiesKHR(VkDevice device, VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetDeviceGroupPresentCapabilitiesKHR(VkDevice device, VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetDeviceGroupSurfacePresentModesKHR(VkDevice device, VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHR* pModes) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetDeviceGroupSurfacePresentModesKHR(VkDevice device, VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHR* pModes) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetDeviceGroupSurfacePresentModesKHR(VkDevice device, VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHR* pModes) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetDeviceGroupSurfacePresentModesKHR(VkDevice device, VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHR* pModes) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetDeviceGroupSurfacePresentModesKHR(VkDevice device, VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHR* pModes) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetDeviceGroupSurfacePresentModesKHR(VkDevice device, VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHR* pModes) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetDeviceGroupSurfacePresentModesKHR(VkDevice device, VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHR* pModes) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetDeviceGroupSurfacePresentModesKHR(VkDevice device, VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHR* pModes) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_AcquireNextImage2KHR(VkDevice device, const VkAcquireNextImageInfoKHR* pAcquireInfo, uint32_t* pImageIndex) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_AcquireNextImage2KHR(VkDevice device, const VkAcquireNextImageInfoKHR* pAcquireInfo, uint32_t* pImageIndex) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_AcquireNextImage2KHR(VkDevice device, const VkAcquireNextImageInfoKHR* pAcquireInfo, uint32_t* pImageIndex) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_AcquireNextImage2KHR(VkDevice device, const VkAcquireNextImageInfoKHR* pAcquireInfo, uint32_t* pImageIndex) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_AcquireNextImage2KHR(VkDevice device, const VkAcquireNextImageInfoKHR* pAcquireInfo, uint32_t* pImageIndex) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_AcquireNextImage2KHR(VkDevice device, const VkAcquireNextImageInfoKHR* pAcquireInfo, uint32_t* pImageIndex) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_AcquireNextImage2KHR(VkDevice device, const VkAcquireNextImageInfoKHR* pAcquireInfo, uint32_t* pImageIndex) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_AcquireNextImage2KHR(VkDevice device, const VkAcquireNextImageInfoKHR* pAcquireInfo, uint32_t* pImageIndex) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDispatchBase(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDispatchBase(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDispatchBase(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDispatchBase(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDispatchBase(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDispatchBase(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDispatchBase(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDispatchBase(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDispatchBaseKHR(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDispatchBaseKHR(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDispatchBaseKHR(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDispatchBaseKHR(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDispatchBaseKHR(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDispatchBaseKHR(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDispatchBaseKHR(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDispatchBaseKHR(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateDescriptorUpdateTemplate(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateDescriptorUpdateTemplate(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateDescriptorUpdateTemplate(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateDescriptorUpdateTemplate(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateDescriptorUpdateTemplate(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateDescriptorUpdateTemplate(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateDescriptorUpdateTemplate(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateDescriptorUpdateTemplate(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateDescriptorUpdateTemplateKHR(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateDescriptorUpdateTemplateKHR(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateDescriptorUpdateTemplateKHR(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateDescriptorUpdateTemplateKHR(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateDescriptorUpdateTemplateKHR(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateDescriptorUpdateTemplateKHR(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateDescriptorUpdateTemplateKHR(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateDescriptorUpdateTemplateKHR(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyDescriptorUpdateTemplate(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyDescriptorUpdateTemplate(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyDescriptorUpdateTemplate(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyDescriptorUpdateTemplate(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyDescriptorUpdateTemplate(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyDescriptorUpdateTemplate(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyDescriptorUpdateTemplate(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyDescriptorUpdateTemplate(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyDescriptorUpdateTemplateKHR(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyDescriptorUpdateTemplateKHR(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyDescriptorUpdateTemplateKHR(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyDescriptorUpdateTemplateKHR(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyDescriptorUpdateTemplateKHR(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyDescriptorUpdateTemplateKHR(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyDescriptorUpdateTemplateKHR(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyDescriptorUpdateTemplateKHR(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_UpdateDescriptorSetWithTemplate(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_UpdateDescriptorSetWithTemplate(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_UpdateDescriptorSetWithTemplate(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_UpdateDescriptorSetWithTemplate(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_UpdateDescriptorSetWithTemplate(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_UpdateDescriptorSetWithTemplate(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_UpdateDescriptorSetWithTemplate(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_UpdateDescriptorSetWithTemplate(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_UpdateDescriptorSetWithTemplateKHR(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_UpdateDescriptorSetWithTemplateKHR(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_UpdateDescriptorSetWithTemplateKHR(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_UpdateDescriptorSetWithTemplateKHR(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_UpdateDescriptorSetWithTemplateKHR(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_UpdateDescriptorSetWithTemplateKHR(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_UpdateDescriptorSetWithTemplateKHR(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_UpdateDescriptorSetWithTemplateKHR(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdPushDescriptorSetWithTemplateKHR(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdPushDescriptorSetWithTemplateKHR(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdPushDescriptorSetWithTemplateKHR(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdPushDescriptorSetWithTemplateKHR(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdPushDescriptorSetWithTemplateKHR(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdPushDescriptorSetWithTemplateKHR(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdPushDescriptorSetWithTemplateKHR(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdPushDescriptorSetWithTemplateKHR(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void* pData) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_SetHdrMetadataEXT(VkDevice device, uint32_t swapchainCount, const VkSwapchainKHR* pSwapchains, const VkHdrMetadataEXT* pMetadata) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_SetHdrMetadataEXT(VkDevice device, uint32_t swapchainCount, const VkSwapchainKHR* pSwapchains, const VkHdrMetadataEXT* pMetadata) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_SetHdrMetadataEXT(VkDevice device, uint32_t swapchainCount, const VkSwapchainKHR* pSwapchains, const VkHdrMetadataEXT* pMetadata) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_SetHdrMetadataEXT(VkDevice device, uint32_t swapchainCount, const VkSwapchainKHR* pSwapchains, const VkHdrMetadataEXT* pMetadata) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_SetHdrMetadataEXT(VkDevice device, uint32_t swapchainCount, const VkSwapchainKHR* pSwapchains, const VkHdrMetadataEXT* pMetadata) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_SetHdrMetadataEXT(VkDevice device, uint32_t swapchainCount, const VkSwapchainKHR* pSwapchains, const VkHdrMetadataEXT* pMetadata) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_SetHdrMetadataEXT(VkDevice device, uint32_t swapchainCount, const VkSwapchainKHR* pSwapchains, const VkHdrMetadataEXT* pMetadata) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_SetHdrMetadataEXT(VkDevice device, uint32_t swapchainCount, const VkSwapchainKHR* pSwapchains, const VkHdrMetadataEXT* pMetadata) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetSwapchainStatusKHR(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetSwapchainStatusKHR(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetSwapchainStatusKHR(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetSwapchainStatusKHR(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetSwapchainStatusKHR(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetSwapchainStatusKHR(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetSwapchainStatusKHR(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetSwapchainStatusKHR(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetRefreshCycleDurationGOOGLE(VkDevice device, VkSwapchainKHR swapchain, VkRefreshCycleDurationGOOGLE* pDisplayTimingProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetRefreshCycleDurationGOOGLE(VkDevice device, VkSwapchainKHR swapchain, VkRefreshCycleDurationGOOGLE* pDisplayTimingProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetRefreshCycleDurationGOOGLE(VkDevice device, VkSwapchainKHR swapchain, VkRefreshCycleDurationGOOGLE* pDisplayTimingProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetRefreshCycleDurationGOOGLE(VkDevice device, VkSwapchainKHR swapchain, VkRefreshCycleDurationGOOGLE* pDisplayTimingProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetRefreshCycleDurationGOOGLE(VkDevice device, VkSwapchainKHR swapchain, VkRefreshCycleDurationGOOGLE* pDisplayTimingProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetRefreshCycleDurationGOOGLE(VkDevice device, VkSwapchainKHR swapchain, VkRefreshCycleDurationGOOGLE* pDisplayTimingProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetRefreshCycleDurationGOOGLE(VkDevice device, VkSwapchainKHR swapchain, VkRefreshCycleDurationGOOGLE* pDisplayTimingProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetRefreshCycleDurationGOOGLE(VkDevice device, VkSwapchainKHR swapchain, VkRefreshCycleDurationGOOGLE* pDisplayTimingProperties) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPastPresentationTimingGOOGLE(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pPresentationTimingCount, VkPastPresentationTimingGOOGLE* pPresentationTimings) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetPastPresentationTimingGOOGLE(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pPresentationTimingCount, VkPastPresentationTimingGOOGLE* pPresentationTimings) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetPastPresentationTimingGOOGLE(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pPresentationTimingCount, VkPastPresentationTimingGOOGLE* pPresentationTimings) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetPastPresentationTimingGOOGLE(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pPresentationTimingCount, VkPastPresentationTimingGOOGLE* pPresentationTimings) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetPastPresentationTimingGOOGLE(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pPresentationTimingCount, VkPastPresentationTimingGOOGLE* pPresentationTimings) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetPastPresentationTimingGOOGLE(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pPresentationTimingCount, VkPastPresentationTimingGOOGLE* pPresentationTimings) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetPastPresentationTimingGOOGLE(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pPresentationTimingCount, VkPastPresentationTimingGOOGLE* pPresentationTimings) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetPastPresentationTimingGOOGLE(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pPresentationTimingCount, VkPastPresentationTimingGOOGLE* pPresentationTimings) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetViewportWScalingNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportWScalingNV* pViewportWScalings) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetViewportWScalingNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportWScalingNV* pViewportWScalings) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetViewportWScalingNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportWScalingNV* pViewportWScalings) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetViewportWScalingNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportWScalingNV* pViewportWScalings) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetViewportWScalingNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportWScalingNV* pViewportWScalings) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetViewportWScalingNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportWScalingNV* pViewportWScalings) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetViewportWScalingNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportWScalingNV* pViewportWScalings) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetViewportWScalingNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportWScalingNV* pViewportWScalings) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetDiscardRectangleEXT(VkCommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const VkRect2D* pDiscardRectangles) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetDiscardRectangleEXT(VkCommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const VkRect2D* pDiscardRectangles) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetDiscardRectangleEXT(VkCommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const VkRect2D* pDiscardRectangles) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetDiscardRectangleEXT(VkCommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const VkRect2D* pDiscardRectangles) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetDiscardRectangleEXT(VkCommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const VkRect2D* pDiscardRectangles) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetDiscardRectangleEXT(VkCommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const VkRect2D* pDiscardRectangles) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetDiscardRectangleEXT(VkCommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const VkRect2D* pDiscardRectangles) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetDiscardRectangleEXT(VkCommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const VkRect2D* pDiscardRectangles) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetDiscardRectangleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 discardRectangleEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetDiscardRectangleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 discardRectangleEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetDiscardRectangleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 discardRectangleEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetDiscardRectangleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 discardRectangleEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetDiscardRectangleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 discardRectangleEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetDiscardRectangleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 discardRectangleEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetDiscardRectangleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 discardRectangleEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetDiscardRectangleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 discardRectangleEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetDiscardRectangleModeEXT(VkCommandBuffer commandBuffer, VkDiscardRectangleModeEXT discardRectangleMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetDiscardRectangleModeEXT(VkCommandBuffer commandBuffer, VkDiscardRectangleModeEXT discardRectangleMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetDiscardRectangleModeEXT(VkCommandBuffer commandBuffer, VkDiscardRectangleModeEXT discardRectangleMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetDiscardRectangleModeEXT(VkCommandBuffer commandBuffer, VkDiscardRectangleModeEXT discardRectangleMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetDiscardRectangleModeEXT(VkCommandBuffer commandBuffer, VkDiscardRectangleModeEXT discardRectangleMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetDiscardRectangleModeEXT(VkCommandBuffer commandBuffer, VkDiscardRectangleModeEXT discardRectangleMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetDiscardRectangleModeEXT(VkCommandBuffer commandBuffer, VkDiscardRectangleModeEXT discardRectangleMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetDiscardRectangleModeEXT(VkCommandBuffer commandBuffer, VkDiscardRectangleModeEXT discardRectangleMode) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetSampleLocationsEXT(VkCommandBuffer commandBuffer, const VkSampleLocationsInfoEXT* pSampleLocationsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetSampleLocationsEXT(VkCommandBuffer commandBuffer, const VkSampleLocationsInfoEXT* pSampleLocationsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetSampleLocationsEXT(VkCommandBuffer commandBuffer, const VkSampleLocationsInfoEXT* pSampleLocationsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetSampleLocationsEXT(VkCommandBuffer commandBuffer, const VkSampleLocationsInfoEXT* pSampleLocationsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetSampleLocationsEXT(VkCommandBuffer commandBuffer, const VkSampleLocationsInfoEXT* pSampleLocationsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetSampleLocationsEXT(VkCommandBuffer commandBuffer, const VkSampleLocationsInfoEXT* pSampleLocationsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetSampleLocationsEXT(VkCommandBuffer commandBuffer, const VkSampleLocationsInfoEXT* pSampleLocationsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetSampleLocationsEXT(VkCommandBuffer commandBuffer, const VkSampleLocationsInfoEXT* pSampleLocationsInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetBufferMemoryRequirements2(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetBufferMemoryRequirements2(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetBufferMemoryRequirements2(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetBufferMemoryRequirements2(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetBufferMemoryRequirements2(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetBufferMemoryRequirements2(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetBufferMemoryRequirements2(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetBufferMemoryRequirements2(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetBufferMemoryRequirements2KHR(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetBufferMemoryRequirements2KHR(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetBufferMemoryRequirements2KHR(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetBufferMemoryRequirements2KHR(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetBufferMemoryRequirements2KHR(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetBufferMemoryRequirements2KHR(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetBufferMemoryRequirements2KHR(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetBufferMemoryRequirements2KHR(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetImageMemoryRequirements2(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetImageMemoryRequirements2(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetImageMemoryRequirements2(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetImageMemoryRequirements2(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetImageMemoryRequirements2(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetImageMemoryRequirements2(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetImageMemoryRequirements2(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetImageMemoryRequirements2(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetImageMemoryRequirements2KHR(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetImageMemoryRequirements2KHR(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetImageMemoryRequirements2KHR(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetImageMemoryRequirements2KHR(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetImageMemoryRequirements2KHR(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetImageMemoryRequirements2KHR(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetImageMemoryRequirements2KHR(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetImageMemoryRequirements2KHR(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetImageSparseMemoryRequirements2(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetImageSparseMemoryRequirements2(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetImageSparseMemoryRequirements2(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetImageSparseMemoryRequirements2(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetImageSparseMemoryRequirements2(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetImageSparseMemoryRequirements2(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetImageSparseMemoryRequirements2(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetImageSparseMemoryRequirements2(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetImageSparseMemoryRequirements2KHR(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetImageSparseMemoryRequirements2KHR(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetImageSparseMemoryRequirements2KHR(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetImageSparseMemoryRequirements2KHR(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetImageSparseMemoryRequirements2KHR(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetImageSparseMemoryRequirements2KHR(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetImageSparseMemoryRequirements2KHR(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetImageSparseMemoryRequirements2KHR(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetDeviceBufferMemoryRequirements(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetDeviceBufferMemoryRequirements(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetDeviceBufferMemoryRequirements(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetDeviceBufferMemoryRequirements(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetDeviceBufferMemoryRequirements(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetDeviceBufferMemoryRequirements(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetDeviceBufferMemoryRequirements(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetDeviceBufferMemoryRequirements(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetDeviceBufferMemoryRequirementsKHR(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetDeviceBufferMemoryRequirementsKHR(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetDeviceBufferMemoryRequirementsKHR(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetDeviceBufferMemoryRequirementsKHR(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetDeviceBufferMemoryRequirementsKHR(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetDeviceBufferMemoryRequirementsKHR(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetDeviceBufferMemoryRequirementsKHR(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetDeviceBufferMemoryRequirementsKHR(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetDeviceImageMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetDeviceImageMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetDeviceImageMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetDeviceImageMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetDeviceImageMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetDeviceImageMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetDeviceImageMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetDeviceImageMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetDeviceImageMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetDeviceImageMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetDeviceImageMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetDeviceImageMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetDeviceImageMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetDeviceImageMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetDeviceImageMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetDeviceImageMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetDeviceImageSparseMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetDeviceImageSparseMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetDeviceImageSparseMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetDeviceImageSparseMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetDeviceImageSparseMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetDeviceImageSparseMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetDeviceImageSparseMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetDeviceImageSparseMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetDeviceImageSparseMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetDeviceImageSparseMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetDeviceImageSparseMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetDeviceImageSparseMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetDeviceImageSparseMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetDeviceImageSparseMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetDeviceImageSparseMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetDeviceImageSparseMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateSamplerYcbcrConversion(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateSamplerYcbcrConversion(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateSamplerYcbcrConversion(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateSamplerYcbcrConversion(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateSamplerYcbcrConversion(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateSamplerYcbcrConversion(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateSamplerYcbcrConversion(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateSamplerYcbcrConversion(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateSamplerYcbcrConversionKHR(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateSamplerYcbcrConversionKHR(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateSamplerYcbcrConversionKHR(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateSamplerYcbcrConversionKHR(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateSamplerYcbcrConversionKHR(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateSamplerYcbcrConversionKHR(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateSamplerYcbcrConversionKHR(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateSamplerYcbcrConversionKHR(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroySamplerYcbcrConversion(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroySamplerYcbcrConversion(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroySamplerYcbcrConversion(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroySamplerYcbcrConversion(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroySamplerYcbcrConversion(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroySamplerYcbcrConversion(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroySamplerYcbcrConversion(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroySamplerYcbcrConversion(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroySamplerYcbcrConversionKHR(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroySamplerYcbcrConversionKHR(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroySamplerYcbcrConversionKHR(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroySamplerYcbcrConversionKHR(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroySamplerYcbcrConversionKHR(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroySamplerYcbcrConversionKHR(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroySamplerYcbcrConversionKHR(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroySamplerYcbcrConversionKHR(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetDeviceQueue2(VkDevice device, const VkDeviceQueueInfo2* pQueueInfo, VkQueue* pQueue) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetDeviceQueue2(VkDevice device, const VkDeviceQueueInfo2* pQueueInfo, VkQueue* pQueue) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetDeviceQueue2(VkDevice device, const VkDeviceQueueInfo2* pQueueInfo, VkQueue* pQueue) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetDeviceQueue2(VkDevice device, const VkDeviceQueueInfo2* pQueueInfo, VkQueue* pQueue) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetDeviceQueue2(VkDevice device, const VkDeviceQueueInfo2* pQueueInfo, VkQueue* pQueue) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetDeviceQueue2(VkDevice device, const VkDeviceQueueInfo2* pQueueInfo, VkQueue* pQueue) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetDeviceQueue2(VkDevice device, const VkDeviceQueueInfo2* pQueueInfo, VkQueue* pQueue) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetDeviceQueue2(VkDevice device, const VkDeviceQueueInfo2* pQueueInfo, VkQueue* pQueue) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateValidationCacheEXT(VkDevice device, const VkValidationCacheCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkValidationCacheEXT* pValidationCache) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateValidationCacheEXT(VkDevice device, const VkValidationCacheCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkValidationCacheEXT* pValidationCache) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateValidationCacheEXT(VkDevice device, const VkValidationCacheCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkValidationCacheEXT* pValidationCache) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateValidationCacheEXT(VkDevice device, const VkValidationCacheCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkValidationCacheEXT* pValidationCache) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateValidationCacheEXT(VkDevice device, const VkValidationCacheCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkValidationCacheEXT* pValidationCache) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateValidationCacheEXT(VkDevice device, const VkValidationCacheCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkValidationCacheEXT* pValidationCache) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateValidationCacheEXT(VkDevice device, const VkValidationCacheCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkValidationCacheEXT* pValidationCache) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateValidationCacheEXT(VkDevice device, const VkValidationCacheCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkValidationCacheEXT* pValidationCache) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyValidationCacheEXT(VkDevice device, VkValidationCacheEXT validationCache, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyValidationCacheEXT(VkDevice device, VkValidationCacheEXT validationCache, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyValidationCacheEXT(VkDevice device, VkValidationCacheEXT validationCache, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyValidationCacheEXT(VkDevice device, VkValidationCacheEXT validationCache, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyValidationCacheEXT(VkDevice device, VkValidationCacheEXT validationCache, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyValidationCacheEXT(VkDevice device, VkValidationCacheEXT validationCache, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyValidationCacheEXT(VkDevice device, VkValidationCacheEXT validationCache, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyValidationCacheEXT(VkDevice device, VkValidationCacheEXT validationCache, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetValidationCacheDataEXT(VkDevice device, VkValidationCacheEXT validationCache, size_t* pDataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetValidationCacheDataEXT(VkDevice device, VkValidationCacheEXT validationCache, size_t* pDataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetValidationCacheDataEXT(VkDevice device, VkValidationCacheEXT validationCache, size_t* pDataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetValidationCacheDataEXT(VkDevice device, VkValidationCacheEXT validationCache, size_t* pDataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetValidationCacheDataEXT(VkDevice device, VkValidationCacheEXT validationCache, size_t* pDataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetValidationCacheDataEXT(VkDevice device, VkValidationCacheEXT validationCache, size_t* pDataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetValidationCacheDataEXT(VkDevice device, VkValidationCacheEXT validationCache, size_t* pDataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetValidationCacheDataEXT(VkDevice device, VkValidationCacheEXT validationCache, size_t* pDataSize, void* pData) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_MergeValidationCachesEXT(VkDevice device, VkValidationCacheEXT dstCache, uint32_t srcCacheCount, const VkValidationCacheEXT* pSrcCaches) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_MergeValidationCachesEXT(VkDevice device, VkValidationCacheEXT dstCache, uint32_t srcCacheCount, const VkValidationCacheEXT* pSrcCaches) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_MergeValidationCachesEXT(VkDevice device, VkValidationCacheEXT dstCache, uint32_t srcCacheCount, const VkValidationCacheEXT* pSrcCaches) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_MergeValidationCachesEXT(VkDevice device, VkValidationCacheEXT dstCache, uint32_t srcCacheCount, const VkValidationCacheEXT* pSrcCaches) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_MergeValidationCachesEXT(VkDevice device, VkValidationCacheEXT dstCache, uint32_t srcCacheCount, const VkValidationCacheEXT* pSrcCaches) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_MergeValidationCachesEXT(VkDevice device, VkValidationCacheEXT dstCache, uint32_t srcCacheCount, const VkValidationCacheEXT* pSrcCaches) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_MergeValidationCachesEXT(VkDevice device, VkValidationCacheEXT dstCache, uint32_t srcCacheCount, const VkValidationCacheEXT* pSrcCaches) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_MergeValidationCachesEXT(VkDevice device, VkValidationCacheEXT dstCache, uint32_t srcCacheCount, const VkValidationCacheEXT* pSrcCaches) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetDescriptorSetLayoutSupport(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetDescriptorSetLayoutSupport(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetDescriptorSetLayoutSupport(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetDescriptorSetLayoutSupport(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetDescriptorSetLayoutSupport(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetDescriptorSetLayoutSupport(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetDescriptorSetLayoutSupport(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetDescriptorSetLayoutSupport(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetDescriptorSetLayoutSupportKHR(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetDescriptorSetLayoutSupportKHR(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetDescriptorSetLayoutSupportKHR(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetDescriptorSetLayoutSupportKHR(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetDescriptorSetLayoutSupportKHR(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetDescriptorSetLayoutSupportKHR(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetDescriptorSetLayoutSupportKHR(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetDescriptorSetLayoutSupportKHR(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) ATTR_WEAK;


#ifdef VK_USE_PLATFORM_ANDROID_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetSwapchainGrallocUsageANDROID(VkDevice device, VkFormat format, VkImageUsageFlags imageUsage, int* grallocUsage) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetSwapchainGrallocUsageANDROID(VkDevice device, VkFormat format, VkImageUsageFlags imageUsage, int* grallocUsage) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetSwapchainGrallocUsageANDROID(VkDevice device, VkFormat format, VkImageUsageFlags imageUsage, int* grallocUsage) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetSwapchainGrallocUsageANDROID(VkDevice device, VkFormat format, VkImageUsageFlags imageUsage, int* grallocUsage) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetSwapchainGrallocUsageANDROID(VkDevice device, VkFormat format, VkImageUsageFlags imageUsage, int* grallocUsage) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetSwapchainGrallocUsageANDROID(VkDevice device, VkFormat format, VkImageUsageFlags imageUsage, int* grallocUsage) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetSwapchainGrallocUsageANDROID(VkDevice device, VkFormat format, VkImageUsageFlags imageUsage, int* grallocUsage) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetSwapchainGrallocUsageANDROID(VkDevice device, VkFormat format, VkImageUsageFlags imageUsage, int* grallocUsage) ATTR_WEAK;


#endif // VK_USE_PLATFORM_ANDROID_KHR
#ifdef VK_USE_PLATFORM_ANDROID_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetSwapchainGrallocUsage2ANDROID(VkDevice device, VkFormat format, VkImageUsageFlags imageUsage, VkSwapchainImageUsageFlagsANDROID swapchainImageUsage, uint64_t* grallocConsumerUsage, uint64_t* grallocProducerUsage) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetSwapchainGrallocUsage2ANDROID(VkDevice device, VkFormat format, VkImageUsageFlags imageUsage, VkSwapchainImageUsageFlagsANDROID swapchainImageUsage, uint64_t* grallocConsumerUsage, uint64_t* grallocProducerUsage) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetSwapchainGrallocUsage2ANDROID(VkDevice device, VkFormat format, VkImageUsageFlags imageUsage, VkSwapchainImageUsageFlagsANDROID swapchainImageUsage, uint64_t* grallocConsumerUsage, uint64_t* grallocProducerUsage) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetSwapchainGrallocUsage2ANDROID(VkDevice device, VkFormat format, VkImageUsageFlags imageUsage, VkSwapchainImageUsageFlagsANDROID swapchainImageUsage, uint64_t* grallocConsumerUsage, uint64_t* grallocProducerUsage) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetSwapchainGrallocUsage2ANDROID(VkDevice device, VkFormat format, VkImageUsageFlags imageUsage, VkSwapchainImageUsageFlagsANDROID swapchainImageUsage, uint64_t* grallocConsumerUsage, uint64_t* grallocProducerUsage) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetSwapchainGrallocUsage2ANDROID(VkDevice device, VkFormat format, VkImageUsageFlags imageUsage, VkSwapchainImageUsageFlagsANDROID swapchainImageUsage, uint64_t* grallocConsumerUsage, uint64_t* grallocProducerUsage) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetSwapchainGrallocUsage2ANDROID(VkDevice device, VkFormat format, VkImageUsageFlags imageUsage, VkSwapchainImageUsageFlagsANDROID swapchainImageUsage, uint64_t* grallocConsumerUsage, uint64_t* grallocProducerUsage) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetSwapchainGrallocUsage2ANDROID(VkDevice device, VkFormat format, VkImageUsageFlags imageUsage, VkSwapchainImageUsageFlagsANDROID swapchainImageUsage, uint64_t* grallocConsumerUsage, uint64_t* grallocProducerUsage) ATTR_WEAK;


#endif // VK_USE_PLATFORM_ANDROID_KHR
#ifdef VK_USE_PLATFORM_ANDROID_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_AcquireImageANDROID(VkDevice device, VkImage image, int nativeFenceFd, VkSemaphore semaphore, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_AcquireImageANDROID(VkDevice device, VkImage image, int nativeFenceFd, VkSemaphore semaphore, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_AcquireImageANDROID(VkDevice device, VkImage image, int nativeFenceFd, VkSemaphore semaphore, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_AcquireImageANDROID(VkDevice device, VkImage image, int nativeFenceFd, VkSemaphore semaphore, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_AcquireImageANDROID(VkDevice device, VkImage image, int nativeFenceFd, VkSemaphore semaphore, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_AcquireImageANDROID(VkDevice device, VkImage image, int nativeFenceFd, VkSemaphore semaphore, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_AcquireImageANDROID(VkDevice device, VkImage image, int nativeFenceFd, VkSemaphore semaphore, VkFence fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_AcquireImageANDROID(VkDevice device, VkImage image, int nativeFenceFd, VkSemaphore semaphore, VkFence fence) ATTR_WEAK;


#endif // VK_USE_PLATFORM_ANDROID_KHR
#ifdef VK_USE_PLATFORM_ANDROID_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_QueueSignalReleaseImageANDROID(VkQueue queue, uint32_t waitSemaphoreCount, const VkSemaphore* pWaitSemaphores, VkImage image, int* pNativeFenceFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_QueueSignalReleaseImageANDROID(VkQueue queue, uint32_t waitSemaphoreCount, const VkSemaphore* pWaitSemaphores, VkImage image, int* pNativeFenceFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_QueueSignalReleaseImageANDROID(VkQueue queue, uint32_t waitSemaphoreCount, const VkSemaphore* pWaitSemaphores, VkImage image, int* pNativeFenceFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_QueueSignalReleaseImageANDROID(VkQueue queue, uint32_t waitSemaphoreCount, const VkSemaphore* pWaitSemaphores, VkImage image, int* pNativeFenceFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_QueueSignalReleaseImageANDROID(VkQueue queue, uint32_t waitSemaphoreCount, const VkSemaphore* pWaitSemaphores, VkImage image, int* pNativeFenceFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_QueueSignalReleaseImageANDROID(VkQueue queue, uint32_t waitSemaphoreCount, const VkSemaphore* pWaitSemaphores, VkImage image, int* pNativeFenceFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_QueueSignalReleaseImageANDROID(VkQueue queue, uint32_t waitSemaphoreCount, const VkSemaphore* pWaitSemaphores, VkImage image, int* pNativeFenceFd) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_QueueSignalReleaseImageANDROID(VkQueue queue, uint32_t waitSemaphoreCount, const VkSemaphore* pWaitSemaphores, VkImage image, int* pNativeFenceFd) ATTR_WEAK;


#endif // VK_USE_PLATFORM_ANDROID_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetShaderInfoAMD(VkDevice device, VkPipeline pipeline, VkShaderStageFlagBits shaderStage, VkShaderInfoTypeAMD infoType, size_t* pInfoSize, void* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetShaderInfoAMD(VkDevice device, VkPipeline pipeline, VkShaderStageFlagBits shaderStage, VkShaderInfoTypeAMD infoType, size_t* pInfoSize, void* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetShaderInfoAMD(VkDevice device, VkPipeline pipeline, VkShaderStageFlagBits shaderStage, VkShaderInfoTypeAMD infoType, size_t* pInfoSize, void* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetShaderInfoAMD(VkDevice device, VkPipeline pipeline, VkShaderStageFlagBits shaderStage, VkShaderInfoTypeAMD infoType, size_t* pInfoSize, void* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetShaderInfoAMD(VkDevice device, VkPipeline pipeline, VkShaderStageFlagBits shaderStage, VkShaderInfoTypeAMD infoType, size_t* pInfoSize, void* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetShaderInfoAMD(VkDevice device, VkPipeline pipeline, VkShaderStageFlagBits shaderStage, VkShaderInfoTypeAMD infoType, size_t* pInfoSize, void* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetShaderInfoAMD(VkDevice device, VkPipeline pipeline, VkShaderStageFlagBits shaderStage, VkShaderInfoTypeAMD infoType, size_t* pInfoSize, void* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetShaderInfoAMD(VkDevice device, VkPipeline pipeline, VkShaderStageFlagBits shaderStage, VkShaderInfoTypeAMD infoType, size_t* pInfoSize, void* pInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_SetLocalDimmingAMD(VkDevice device, VkSwapchainKHR swapChain, VkBool32 localDimmingEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_SetLocalDimmingAMD(VkDevice device, VkSwapchainKHR swapChain, VkBool32 localDimmingEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_SetLocalDimmingAMD(VkDevice device, VkSwapchainKHR swapChain, VkBool32 localDimmingEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_SetLocalDimmingAMD(VkDevice device, VkSwapchainKHR swapChain, VkBool32 localDimmingEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_SetLocalDimmingAMD(VkDevice device, VkSwapchainKHR swapChain, VkBool32 localDimmingEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_SetLocalDimmingAMD(VkDevice device, VkSwapchainKHR swapChain, VkBool32 localDimmingEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_SetLocalDimmingAMD(VkDevice device, VkSwapchainKHR swapChain, VkBool32 localDimmingEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_SetLocalDimmingAMD(VkDevice device, VkSwapchainKHR swapChain, VkBool32 localDimmingEnable) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetCalibratedTimestampsEXT(VkDevice device, uint32_t timestampCount, const VkCalibratedTimestampInfoEXT* pTimestampInfos, uint64_t* pTimestamps, uint64_t* pMaxDeviation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetCalibratedTimestampsEXT(VkDevice device, uint32_t timestampCount, const VkCalibratedTimestampInfoEXT* pTimestampInfos, uint64_t* pTimestamps, uint64_t* pMaxDeviation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetCalibratedTimestampsEXT(VkDevice device, uint32_t timestampCount, const VkCalibratedTimestampInfoEXT* pTimestampInfos, uint64_t* pTimestamps, uint64_t* pMaxDeviation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetCalibratedTimestampsEXT(VkDevice device, uint32_t timestampCount, const VkCalibratedTimestampInfoEXT* pTimestampInfos, uint64_t* pTimestamps, uint64_t* pMaxDeviation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetCalibratedTimestampsEXT(VkDevice device, uint32_t timestampCount, const VkCalibratedTimestampInfoEXT* pTimestampInfos, uint64_t* pTimestamps, uint64_t* pMaxDeviation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetCalibratedTimestampsEXT(VkDevice device, uint32_t timestampCount, const VkCalibratedTimestampInfoEXT* pTimestampInfos, uint64_t* pTimestamps, uint64_t* pMaxDeviation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetCalibratedTimestampsEXT(VkDevice device, uint32_t timestampCount, const VkCalibratedTimestampInfoEXT* pTimestampInfos, uint64_t* pTimestamps, uint64_t* pMaxDeviation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetCalibratedTimestampsEXT(VkDevice device, uint32_t timestampCount, const VkCalibratedTimestampInfoEXT* pTimestampInfos, uint64_t* pTimestamps, uint64_t* pMaxDeviation) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_SetDebugUtilsObjectNameEXT(VkDevice device, const VkDebugUtilsObjectNameInfoEXT* pNameInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_SetDebugUtilsObjectNameEXT(VkDevice device, const VkDebugUtilsObjectNameInfoEXT* pNameInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_SetDebugUtilsObjectNameEXT(VkDevice device, const VkDebugUtilsObjectNameInfoEXT* pNameInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_SetDebugUtilsObjectNameEXT(VkDevice device, const VkDebugUtilsObjectNameInfoEXT* pNameInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_SetDebugUtilsObjectNameEXT(VkDevice device, const VkDebugUtilsObjectNameInfoEXT* pNameInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_SetDebugUtilsObjectNameEXT(VkDevice device, const VkDebugUtilsObjectNameInfoEXT* pNameInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_SetDebugUtilsObjectNameEXT(VkDevice device, const VkDebugUtilsObjectNameInfoEXT* pNameInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_SetDebugUtilsObjectNameEXT(VkDevice device, const VkDebugUtilsObjectNameInfoEXT* pNameInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_SetDebugUtilsObjectTagEXT(VkDevice device, const VkDebugUtilsObjectTagInfoEXT* pTagInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_SetDebugUtilsObjectTagEXT(VkDevice device, const VkDebugUtilsObjectTagInfoEXT* pTagInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_SetDebugUtilsObjectTagEXT(VkDevice device, const VkDebugUtilsObjectTagInfoEXT* pTagInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_SetDebugUtilsObjectTagEXT(VkDevice device, const VkDebugUtilsObjectTagInfoEXT* pTagInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_SetDebugUtilsObjectTagEXT(VkDevice device, const VkDebugUtilsObjectTagInfoEXT* pTagInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_SetDebugUtilsObjectTagEXT(VkDevice device, const VkDebugUtilsObjectTagInfoEXT* pTagInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_SetDebugUtilsObjectTagEXT(VkDevice device, const VkDebugUtilsObjectTagInfoEXT* pTagInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_SetDebugUtilsObjectTagEXT(VkDevice device, const VkDebugUtilsObjectTagInfoEXT* pTagInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_QueueBeginDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_QueueBeginDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_QueueBeginDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_QueueBeginDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_QueueBeginDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_QueueBeginDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_QueueBeginDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_QueueBeginDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_QueueEndDebugUtilsLabelEXT(VkQueue queue) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_QueueEndDebugUtilsLabelEXT(VkQueue queue) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_QueueEndDebugUtilsLabelEXT(VkQueue queue) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_QueueEndDebugUtilsLabelEXT(VkQueue queue) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_QueueEndDebugUtilsLabelEXT(VkQueue queue) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_QueueEndDebugUtilsLabelEXT(VkQueue queue) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_QueueEndDebugUtilsLabelEXT(VkQueue queue) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_QueueEndDebugUtilsLabelEXT(VkQueue queue) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_QueueInsertDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_QueueInsertDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_QueueInsertDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_QueueInsertDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_QueueInsertDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_QueueInsertDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_QueueInsertDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_QueueInsertDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetMemoryHostPointerPropertiesEXT(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, const void* pHostPointer, VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetMemoryHostPointerPropertiesEXT(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, const void* pHostPointer, VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetMemoryHostPointerPropertiesEXT(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, const void* pHostPointer, VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetMemoryHostPointerPropertiesEXT(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, const void* pHostPointer, VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetMemoryHostPointerPropertiesEXT(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, const void* pHostPointer, VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetMemoryHostPointerPropertiesEXT(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, const void* pHostPointer, VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetMemoryHostPointerPropertiesEXT(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, const void* pHostPointer, VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetMemoryHostPointerPropertiesEXT(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, const void* pHostPointer, VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdWriteBufferMarkerAMD(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdWriteBufferMarkerAMD(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdWriteBufferMarkerAMD(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdWriteBufferMarkerAMD(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdWriteBufferMarkerAMD(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdWriteBufferMarkerAMD(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdWriteBufferMarkerAMD(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdWriteBufferMarkerAMD(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateRenderPass2(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateRenderPass2(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateRenderPass2(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateRenderPass2(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateRenderPass2(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateRenderPass2(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateRenderPass2(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateRenderPass2(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateRenderPass2KHR(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateRenderPass2KHR(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateRenderPass2KHR(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateRenderPass2KHR(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateRenderPass2KHR(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateRenderPass2KHR(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateRenderPass2KHR(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateRenderPass2KHR(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBeginRenderPass2(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo*      pRenderPassBegin, const VkSubpassBeginInfo*      pSubpassBeginInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBeginRenderPass2(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo*      pRenderPassBegin, const VkSubpassBeginInfo*      pSubpassBeginInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBeginRenderPass2(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo*      pRenderPassBegin, const VkSubpassBeginInfo*      pSubpassBeginInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBeginRenderPass2(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo*      pRenderPassBegin, const VkSubpassBeginInfo*      pSubpassBeginInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBeginRenderPass2(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo*      pRenderPassBegin, const VkSubpassBeginInfo*      pSubpassBeginInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBeginRenderPass2(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo*      pRenderPassBegin, const VkSubpassBeginInfo*      pSubpassBeginInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBeginRenderPass2(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo*      pRenderPassBegin, const VkSubpassBeginInfo*      pSubpassBeginInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBeginRenderPass2(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo*      pRenderPassBegin, const VkSubpassBeginInfo*      pSubpassBeginInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBeginRenderPass2KHR(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo*      pRenderPassBegin, const VkSubpassBeginInfo*      pSubpassBeginInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBeginRenderPass2KHR(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo*      pRenderPassBegin, const VkSubpassBeginInfo*      pSubpassBeginInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBeginRenderPass2KHR(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo*      pRenderPassBegin, const VkSubpassBeginInfo*      pSubpassBeginInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBeginRenderPass2KHR(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo*      pRenderPassBegin, const VkSubpassBeginInfo*      pSubpassBeginInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBeginRenderPass2KHR(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo*      pRenderPassBegin, const VkSubpassBeginInfo*      pSubpassBeginInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBeginRenderPass2KHR(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo*      pRenderPassBegin, const VkSubpassBeginInfo*      pSubpassBeginInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBeginRenderPass2KHR(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo*      pRenderPassBegin, const VkSubpassBeginInfo*      pSubpassBeginInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBeginRenderPass2KHR(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo*      pRenderPassBegin, const VkSubpassBeginInfo*      pSubpassBeginInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdNextSubpass2(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo*      pSubpassBeginInfo, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdNextSubpass2(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo*      pSubpassBeginInfo, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdNextSubpass2(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo*      pSubpassBeginInfo, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdNextSubpass2(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo*      pSubpassBeginInfo, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdNextSubpass2(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo*      pSubpassBeginInfo, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdNextSubpass2(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo*      pSubpassBeginInfo, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdNextSubpass2(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo*      pSubpassBeginInfo, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdNextSubpass2(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo*      pSubpassBeginInfo, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdNextSubpass2KHR(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo*      pSubpassBeginInfo, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdNextSubpass2KHR(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo*      pSubpassBeginInfo, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdNextSubpass2KHR(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo*      pSubpassBeginInfo, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdNextSubpass2KHR(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo*      pSubpassBeginInfo, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdNextSubpass2KHR(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo*      pSubpassBeginInfo, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdNextSubpass2KHR(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo*      pSubpassBeginInfo, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdNextSubpass2KHR(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo*      pSubpassBeginInfo, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdNextSubpass2KHR(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo*      pSubpassBeginInfo, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdEndRenderPass2(VkCommandBuffer commandBuffer, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdEndRenderPass2(VkCommandBuffer commandBuffer, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdEndRenderPass2(VkCommandBuffer commandBuffer, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdEndRenderPass2(VkCommandBuffer commandBuffer, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdEndRenderPass2(VkCommandBuffer commandBuffer, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdEndRenderPass2(VkCommandBuffer commandBuffer, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdEndRenderPass2(VkCommandBuffer commandBuffer, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdEndRenderPass2(VkCommandBuffer commandBuffer, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdEndRenderPass2KHR(VkCommandBuffer commandBuffer, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdEndRenderPass2KHR(VkCommandBuffer commandBuffer, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdEndRenderPass2KHR(VkCommandBuffer commandBuffer, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdEndRenderPass2KHR(VkCommandBuffer commandBuffer, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdEndRenderPass2KHR(VkCommandBuffer commandBuffer, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdEndRenderPass2KHR(VkCommandBuffer commandBuffer, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdEndRenderPass2KHR(VkCommandBuffer commandBuffer, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdEndRenderPass2KHR(VkCommandBuffer commandBuffer, const VkSubpassEndInfo*        pSubpassEndInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetSemaphoreCounterValue(VkDevice device, VkSemaphore semaphore, uint64_t* pValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetSemaphoreCounterValue(VkDevice device, VkSemaphore semaphore, uint64_t* pValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetSemaphoreCounterValue(VkDevice device, VkSemaphore semaphore, uint64_t* pValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetSemaphoreCounterValue(VkDevice device, VkSemaphore semaphore, uint64_t* pValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetSemaphoreCounterValue(VkDevice device, VkSemaphore semaphore, uint64_t* pValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetSemaphoreCounterValue(VkDevice device, VkSemaphore semaphore, uint64_t* pValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetSemaphoreCounterValue(VkDevice device, VkSemaphore semaphore, uint64_t* pValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetSemaphoreCounterValue(VkDevice device, VkSemaphore semaphore, uint64_t* pValue) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetSemaphoreCounterValueKHR(VkDevice device, VkSemaphore semaphore, uint64_t* pValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetSemaphoreCounterValueKHR(VkDevice device, VkSemaphore semaphore, uint64_t* pValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetSemaphoreCounterValueKHR(VkDevice device, VkSemaphore semaphore, uint64_t* pValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetSemaphoreCounterValueKHR(VkDevice device, VkSemaphore semaphore, uint64_t* pValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetSemaphoreCounterValueKHR(VkDevice device, VkSemaphore semaphore, uint64_t* pValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetSemaphoreCounterValueKHR(VkDevice device, VkSemaphore semaphore, uint64_t* pValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetSemaphoreCounterValueKHR(VkDevice device, VkSemaphore semaphore, uint64_t* pValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetSemaphoreCounterValueKHR(VkDevice device, VkSemaphore semaphore, uint64_t* pValue) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_WaitSemaphores(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_WaitSemaphores(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_WaitSemaphores(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_WaitSemaphores(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_WaitSemaphores(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_WaitSemaphores(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_WaitSemaphores(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_WaitSemaphores(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_WaitSemaphoresKHR(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_WaitSemaphoresKHR(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_WaitSemaphoresKHR(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_WaitSemaphoresKHR(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_WaitSemaphoresKHR(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_WaitSemaphoresKHR(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_WaitSemaphoresKHR(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_WaitSemaphoresKHR(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_SignalSemaphore(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_SignalSemaphore(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_SignalSemaphore(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_SignalSemaphore(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_SignalSemaphore(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_SignalSemaphore(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_SignalSemaphore(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_SignalSemaphore(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_SignalSemaphoreKHR(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_SignalSemaphoreKHR(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_SignalSemaphoreKHR(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_SignalSemaphoreKHR(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_SignalSemaphoreKHR(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_SignalSemaphoreKHR(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_SignalSemaphoreKHR(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_SignalSemaphoreKHR(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) ATTR_WEAK;


#ifdef VK_USE_PLATFORM_ANDROID_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetAndroidHardwareBufferPropertiesANDROID(VkDevice device, const struct AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetAndroidHardwareBufferPropertiesANDROID(VkDevice device, const struct AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetAndroidHardwareBufferPropertiesANDROID(VkDevice device, const struct AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetAndroidHardwareBufferPropertiesANDROID(VkDevice device, const struct AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetAndroidHardwareBufferPropertiesANDROID(VkDevice device, const struct AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetAndroidHardwareBufferPropertiesANDROID(VkDevice device, const struct AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetAndroidHardwareBufferPropertiesANDROID(VkDevice device, const struct AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetAndroidHardwareBufferPropertiesANDROID(VkDevice device, const struct AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties) ATTR_WEAK;


#endif // VK_USE_PLATFORM_ANDROID_KHR
#ifdef VK_USE_PLATFORM_ANDROID_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetMemoryAndroidHardwareBufferANDROID(VkDevice device, const VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, struct AHardwareBuffer** pBuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetMemoryAndroidHardwareBufferANDROID(VkDevice device, const VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, struct AHardwareBuffer** pBuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetMemoryAndroidHardwareBufferANDROID(VkDevice device, const VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, struct AHardwareBuffer** pBuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetMemoryAndroidHardwareBufferANDROID(VkDevice device, const VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, struct AHardwareBuffer** pBuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetMemoryAndroidHardwareBufferANDROID(VkDevice device, const VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, struct AHardwareBuffer** pBuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetMemoryAndroidHardwareBufferANDROID(VkDevice device, const VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, struct AHardwareBuffer** pBuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetMemoryAndroidHardwareBufferANDROID(VkDevice device, const VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, struct AHardwareBuffer** pBuffer) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetMemoryAndroidHardwareBufferANDROID(VkDevice device, const VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, struct AHardwareBuffer** pBuffer) ATTR_WEAK;


#endif // VK_USE_PLATFORM_ANDROID_KHR
  VKAPI_ATTR void VKAPI_CALL anv_CmdDrawIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDrawIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDrawIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDrawIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDrawIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDrawIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDrawIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDrawIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDrawIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDrawIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDrawIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDrawIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDrawIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDrawIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDrawIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDrawIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDrawIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDrawIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDrawIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDrawIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDrawIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDrawIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDrawIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDrawIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDrawIndexedIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDrawIndexedIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDrawIndexedIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDrawIndexedIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDrawIndexedIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDrawIndexedIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDrawIndexedIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDrawIndexedIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDrawIndexedIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDrawIndexedIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDrawIndexedIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDrawIndexedIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDrawIndexedIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDrawIndexedIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDrawIndexedIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDrawIndexedIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDrawIndexedIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDrawIndexedIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDrawIndexedIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDrawIndexedIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDrawIndexedIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDrawIndexedIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDrawIndexedIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDrawIndexedIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetCheckpointNV(VkCommandBuffer commandBuffer, const void* pCheckpointMarker) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetCheckpointNV(VkCommandBuffer commandBuffer, const void* pCheckpointMarker) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetCheckpointNV(VkCommandBuffer commandBuffer, const void* pCheckpointMarker) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetCheckpointNV(VkCommandBuffer commandBuffer, const void* pCheckpointMarker) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetCheckpointNV(VkCommandBuffer commandBuffer, const void* pCheckpointMarker) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetCheckpointNV(VkCommandBuffer commandBuffer, const void* pCheckpointMarker) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetCheckpointNV(VkCommandBuffer commandBuffer, const void* pCheckpointMarker) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetCheckpointNV(VkCommandBuffer commandBuffer, const void* pCheckpointMarker) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetQueueCheckpointDataNV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointDataNV* pCheckpointData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetQueueCheckpointDataNV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointDataNV* pCheckpointData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetQueueCheckpointDataNV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointDataNV* pCheckpointData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetQueueCheckpointDataNV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointDataNV* pCheckpointData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetQueueCheckpointDataNV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointDataNV* pCheckpointData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetQueueCheckpointDataNV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointDataNV* pCheckpointData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetQueueCheckpointDataNV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointDataNV* pCheckpointData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetQueueCheckpointDataNV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointDataNV* pCheckpointData) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBindTransformFeedbackBuffersEXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBindTransformFeedbackBuffersEXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBindTransformFeedbackBuffersEXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBindTransformFeedbackBuffersEXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBindTransformFeedbackBuffersEXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBindTransformFeedbackBuffersEXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBindTransformFeedbackBuffersEXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBindTransformFeedbackBuffersEXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBeginTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBeginTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBeginTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBeginTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBeginTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBeginTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBeginTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBeginTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdEndTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdEndTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdEndTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdEndTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdEndTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdEndTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdEndTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdEndTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBeginQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags, uint32_t index) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBeginQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags, uint32_t index) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBeginQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags, uint32_t index) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBeginQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags, uint32_t index) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBeginQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags, uint32_t index) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBeginQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags, uint32_t index) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBeginQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags, uint32_t index) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBeginQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags, uint32_t index) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdEndQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, uint32_t index) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdEndQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, uint32_t index) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdEndQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, uint32_t index) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdEndQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, uint32_t index) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdEndQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, uint32_t index) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdEndQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, uint32_t index) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdEndQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, uint32_t index) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdEndQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, uint32_t index) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDrawIndirectByteCountEXT(VkCommandBuffer commandBuffer, uint32_t instanceCount, uint32_t firstInstance, VkBuffer counterBuffer, VkDeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDrawIndirectByteCountEXT(VkCommandBuffer commandBuffer, uint32_t instanceCount, uint32_t firstInstance, VkBuffer counterBuffer, VkDeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDrawIndirectByteCountEXT(VkCommandBuffer commandBuffer, uint32_t instanceCount, uint32_t firstInstance, VkBuffer counterBuffer, VkDeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDrawIndirectByteCountEXT(VkCommandBuffer commandBuffer, uint32_t instanceCount, uint32_t firstInstance, VkBuffer counterBuffer, VkDeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDrawIndirectByteCountEXT(VkCommandBuffer commandBuffer, uint32_t instanceCount, uint32_t firstInstance, VkBuffer counterBuffer, VkDeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDrawIndirectByteCountEXT(VkCommandBuffer commandBuffer, uint32_t instanceCount, uint32_t firstInstance, VkBuffer counterBuffer, VkDeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDrawIndirectByteCountEXT(VkCommandBuffer commandBuffer, uint32_t instanceCount, uint32_t firstInstance, VkBuffer counterBuffer, VkDeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDrawIndirectByteCountEXT(VkCommandBuffer commandBuffer, uint32_t instanceCount, uint32_t firstInstance, VkBuffer counterBuffer, VkDeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetExclusiveScissorNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkRect2D* pExclusiveScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetExclusiveScissorNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkRect2D* pExclusiveScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetExclusiveScissorNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkRect2D* pExclusiveScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetExclusiveScissorNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkRect2D* pExclusiveScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetExclusiveScissorNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkRect2D* pExclusiveScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetExclusiveScissorNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkRect2D* pExclusiveScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetExclusiveScissorNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkRect2D* pExclusiveScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetExclusiveScissorNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkRect2D* pExclusiveScissors) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetExclusiveScissorEnableNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkBool32* pExclusiveScissorEnables) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetExclusiveScissorEnableNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkBool32* pExclusiveScissorEnables) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetExclusiveScissorEnableNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkBool32* pExclusiveScissorEnables) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetExclusiveScissorEnableNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkBool32* pExclusiveScissorEnables) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetExclusiveScissorEnableNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkBool32* pExclusiveScissorEnables) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetExclusiveScissorEnableNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkBool32* pExclusiveScissorEnables) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetExclusiveScissorEnableNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkBool32* pExclusiveScissorEnables) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetExclusiveScissorEnableNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkBool32* pExclusiveScissorEnables) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBindShadingRateImageNV(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBindShadingRateImageNV(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBindShadingRateImageNV(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBindShadingRateImageNV(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBindShadingRateImageNV(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBindShadingRateImageNV(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBindShadingRateImageNV(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBindShadingRateImageNV(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetViewportShadingRatePaletteNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkShadingRatePaletteNV* pShadingRatePalettes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetViewportShadingRatePaletteNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkShadingRatePaletteNV* pShadingRatePalettes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetViewportShadingRatePaletteNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkShadingRatePaletteNV* pShadingRatePalettes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetViewportShadingRatePaletteNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkShadingRatePaletteNV* pShadingRatePalettes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetViewportShadingRatePaletteNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkShadingRatePaletteNV* pShadingRatePalettes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetViewportShadingRatePaletteNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkShadingRatePaletteNV* pShadingRatePalettes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetViewportShadingRatePaletteNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkShadingRatePaletteNV* pShadingRatePalettes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetViewportShadingRatePaletteNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkShadingRatePaletteNV* pShadingRatePalettes) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetCoarseSampleOrderNV(VkCommandBuffer commandBuffer, VkCoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount, const VkCoarseSampleOrderCustomNV* pCustomSampleOrders) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetCoarseSampleOrderNV(VkCommandBuffer commandBuffer, VkCoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount, const VkCoarseSampleOrderCustomNV* pCustomSampleOrders) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetCoarseSampleOrderNV(VkCommandBuffer commandBuffer, VkCoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount, const VkCoarseSampleOrderCustomNV* pCustomSampleOrders) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetCoarseSampleOrderNV(VkCommandBuffer commandBuffer, VkCoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount, const VkCoarseSampleOrderCustomNV* pCustomSampleOrders) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetCoarseSampleOrderNV(VkCommandBuffer commandBuffer, VkCoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount, const VkCoarseSampleOrderCustomNV* pCustomSampleOrders) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetCoarseSampleOrderNV(VkCommandBuffer commandBuffer, VkCoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount, const VkCoarseSampleOrderCustomNV* pCustomSampleOrders) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetCoarseSampleOrderNV(VkCommandBuffer commandBuffer, VkCoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount, const VkCoarseSampleOrderCustomNV* pCustomSampleOrders) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetCoarseSampleOrderNV(VkCommandBuffer commandBuffer, VkCoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount, const VkCoarseSampleOrderCustomNV* pCustomSampleOrders) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDrawMeshTasksNV(VkCommandBuffer commandBuffer, uint32_t taskCount, uint32_t firstTask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDrawMeshTasksNV(VkCommandBuffer commandBuffer, uint32_t taskCount, uint32_t firstTask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDrawMeshTasksNV(VkCommandBuffer commandBuffer, uint32_t taskCount, uint32_t firstTask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDrawMeshTasksNV(VkCommandBuffer commandBuffer, uint32_t taskCount, uint32_t firstTask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDrawMeshTasksNV(VkCommandBuffer commandBuffer, uint32_t taskCount, uint32_t firstTask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDrawMeshTasksNV(VkCommandBuffer commandBuffer, uint32_t taskCount, uint32_t firstTask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDrawMeshTasksNV(VkCommandBuffer commandBuffer, uint32_t taskCount, uint32_t firstTask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDrawMeshTasksNV(VkCommandBuffer commandBuffer, uint32_t taskCount, uint32_t firstTask) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDrawMeshTasksIndirectNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDrawMeshTasksIndirectNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDrawMeshTasksIndirectNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDrawMeshTasksIndirectNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDrawMeshTasksIndirectNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDrawMeshTasksIndirectNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDrawMeshTasksIndirectNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDrawMeshTasksIndirectNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDrawMeshTasksIndirectCountNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDrawMeshTasksIndirectCountNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDrawMeshTasksIndirectCountNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDrawMeshTasksIndirectCountNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDrawMeshTasksIndirectCountNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDrawMeshTasksIndirectCountNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDrawMeshTasksIndirectCountNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDrawMeshTasksIndirectCountNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDrawMeshTasksEXT(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDrawMeshTasksEXT(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDrawMeshTasksEXT(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDrawMeshTasksEXT(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDrawMeshTasksEXT(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDrawMeshTasksEXT(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDrawMeshTasksEXT(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDrawMeshTasksEXT(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDrawMeshTasksIndirectEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDrawMeshTasksIndirectEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDrawMeshTasksIndirectEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDrawMeshTasksIndirectEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDrawMeshTasksIndirectEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDrawMeshTasksIndirectEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDrawMeshTasksIndirectEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDrawMeshTasksIndirectEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDrawMeshTasksIndirectCountEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDrawMeshTasksIndirectCountEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDrawMeshTasksIndirectCountEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDrawMeshTasksIndirectCountEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDrawMeshTasksIndirectCountEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDrawMeshTasksIndirectCountEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDrawMeshTasksIndirectCountEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDrawMeshTasksIndirectCountEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CompileDeferredNV(VkDevice device, VkPipeline pipeline, uint32_t shader) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CompileDeferredNV(VkDevice device, VkPipeline pipeline, uint32_t shader) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CompileDeferredNV(VkDevice device, VkPipeline pipeline, uint32_t shader) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CompileDeferredNV(VkDevice device, VkPipeline pipeline, uint32_t shader) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CompileDeferredNV(VkDevice device, VkPipeline pipeline, uint32_t shader) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CompileDeferredNV(VkDevice device, VkPipeline pipeline, uint32_t shader) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CompileDeferredNV(VkDevice device, VkPipeline pipeline, uint32_t shader) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CompileDeferredNV(VkDevice device, VkPipeline pipeline, uint32_t shader) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateAccelerationStructureNV(VkDevice device, const VkAccelerationStructureCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureNV* pAccelerationStructure) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateAccelerationStructureNV(VkDevice device, const VkAccelerationStructureCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureNV* pAccelerationStructure) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateAccelerationStructureNV(VkDevice device, const VkAccelerationStructureCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureNV* pAccelerationStructure) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateAccelerationStructureNV(VkDevice device, const VkAccelerationStructureCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureNV* pAccelerationStructure) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateAccelerationStructureNV(VkDevice device, const VkAccelerationStructureCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureNV* pAccelerationStructure) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateAccelerationStructureNV(VkDevice device, const VkAccelerationStructureCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureNV* pAccelerationStructure) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateAccelerationStructureNV(VkDevice device, const VkAccelerationStructureCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureNV* pAccelerationStructure) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateAccelerationStructureNV(VkDevice device, const VkAccelerationStructureCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureNV* pAccelerationStructure) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBindInvocationMaskHUAWEI(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBindInvocationMaskHUAWEI(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBindInvocationMaskHUAWEI(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBindInvocationMaskHUAWEI(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBindInvocationMaskHUAWEI(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBindInvocationMaskHUAWEI(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBindInvocationMaskHUAWEI(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBindInvocationMaskHUAWEI(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyAccelerationStructureKHR(VkDevice device, VkAccelerationStructureKHR accelerationStructure, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyAccelerationStructureKHR(VkDevice device, VkAccelerationStructureKHR accelerationStructure, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyAccelerationStructureKHR(VkDevice device, VkAccelerationStructureKHR accelerationStructure, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyAccelerationStructureKHR(VkDevice device, VkAccelerationStructureKHR accelerationStructure, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyAccelerationStructureKHR(VkDevice device, VkAccelerationStructureKHR accelerationStructure, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyAccelerationStructureKHR(VkDevice device, VkAccelerationStructureKHR accelerationStructure, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyAccelerationStructureKHR(VkDevice device, VkAccelerationStructureKHR accelerationStructure, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyAccelerationStructureKHR(VkDevice device, VkAccelerationStructureKHR accelerationStructure, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyAccelerationStructureNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyAccelerationStructureNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyAccelerationStructureNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyAccelerationStructureNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyAccelerationStructureNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyAccelerationStructureNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyAccelerationStructureNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyAccelerationStructureNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetAccelerationStructureMemoryRequirementsNV(VkDevice device, const VkAccelerationStructureMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetAccelerationStructureMemoryRequirementsNV(VkDevice device, const VkAccelerationStructureMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetAccelerationStructureMemoryRequirementsNV(VkDevice device, const VkAccelerationStructureMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetAccelerationStructureMemoryRequirementsNV(VkDevice device, const VkAccelerationStructureMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetAccelerationStructureMemoryRequirementsNV(VkDevice device, const VkAccelerationStructureMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetAccelerationStructureMemoryRequirementsNV(VkDevice device, const VkAccelerationStructureMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetAccelerationStructureMemoryRequirementsNV(VkDevice device, const VkAccelerationStructureMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetAccelerationStructureMemoryRequirementsNV(VkDevice device, const VkAccelerationStructureMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_BindAccelerationStructureMemoryNV(VkDevice device, uint32_t bindInfoCount, const VkBindAccelerationStructureMemoryInfoNV* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_BindAccelerationStructureMemoryNV(VkDevice device, uint32_t bindInfoCount, const VkBindAccelerationStructureMemoryInfoNV* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_BindAccelerationStructureMemoryNV(VkDevice device, uint32_t bindInfoCount, const VkBindAccelerationStructureMemoryInfoNV* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_BindAccelerationStructureMemoryNV(VkDevice device, uint32_t bindInfoCount, const VkBindAccelerationStructureMemoryInfoNV* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_BindAccelerationStructureMemoryNV(VkDevice device, uint32_t bindInfoCount, const VkBindAccelerationStructureMemoryInfoNV* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_BindAccelerationStructureMemoryNV(VkDevice device, uint32_t bindInfoCount, const VkBindAccelerationStructureMemoryInfoNV* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_BindAccelerationStructureMemoryNV(VkDevice device, uint32_t bindInfoCount, const VkBindAccelerationStructureMemoryInfoNV* pBindInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_BindAccelerationStructureMemoryNV(VkDevice device, uint32_t bindInfoCount, const VkBindAccelerationStructureMemoryInfoNV* pBindInfos) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCopyAccelerationStructureNV(VkCommandBuffer commandBuffer, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkCopyAccelerationStructureModeKHR mode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCopyAccelerationStructureNV(VkCommandBuffer commandBuffer, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkCopyAccelerationStructureModeKHR mode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCopyAccelerationStructureNV(VkCommandBuffer commandBuffer, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkCopyAccelerationStructureModeKHR mode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCopyAccelerationStructureNV(VkCommandBuffer commandBuffer, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkCopyAccelerationStructureModeKHR mode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCopyAccelerationStructureNV(VkCommandBuffer commandBuffer, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkCopyAccelerationStructureModeKHR mode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCopyAccelerationStructureNV(VkCommandBuffer commandBuffer, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkCopyAccelerationStructureModeKHR mode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCopyAccelerationStructureNV(VkCommandBuffer commandBuffer, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkCopyAccelerationStructureModeKHR mode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCopyAccelerationStructureNV(VkCommandBuffer commandBuffer, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkCopyAccelerationStructureModeKHR mode) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCopyAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCopyAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCopyAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCopyAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCopyAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCopyAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCopyAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCopyAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CopyAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CopyAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CopyAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CopyAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CopyAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CopyAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CopyAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CopyAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCopyAccelerationStructureToMemoryKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCopyAccelerationStructureToMemoryKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCopyAccelerationStructureToMemoryKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCopyAccelerationStructureToMemoryKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCopyAccelerationStructureToMemoryKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCopyAccelerationStructureToMemoryKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCopyAccelerationStructureToMemoryKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCopyAccelerationStructureToMemoryKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CopyAccelerationStructureToMemoryKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CopyAccelerationStructureToMemoryKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CopyAccelerationStructureToMemoryKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CopyAccelerationStructureToMemoryKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CopyAccelerationStructureToMemoryKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CopyAccelerationStructureToMemoryKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CopyAccelerationStructureToMemoryKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CopyAccelerationStructureToMemoryKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCopyMemoryToAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCopyMemoryToAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCopyMemoryToAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCopyMemoryToAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCopyMemoryToAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCopyMemoryToAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCopyMemoryToAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCopyMemoryToAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CopyMemoryToAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CopyMemoryToAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CopyMemoryToAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CopyMemoryToAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CopyMemoryToAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CopyMemoryToAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CopyMemoryToAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CopyMemoryToAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdWriteAccelerationStructuresPropertiesKHR(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdWriteAccelerationStructuresPropertiesKHR(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdWriteAccelerationStructuresPropertiesKHR(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdWriteAccelerationStructuresPropertiesKHR(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdWriteAccelerationStructuresPropertiesKHR(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdWriteAccelerationStructuresPropertiesKHR(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdWriteAccelerationStructuresPropertiesKHR(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdWriteAccelerationStructuresPropertiesKHR(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdWriteAccelerationStructuresPropertiesNV(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureNV* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdWriteAccelerationStructuresPropertiesNV(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureNV* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdWriteAccelerationStructuresPropertiesNV(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureNV* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdWriteAccelerationStructuresPropertiesNV(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureNV* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdWriteAccelerationStructuresPropertiesNV(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureNV* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdWriteAccelerationStructuresPropertiesNV(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureNV* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdWriteAccelerationStructuresPropertiesNV(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureNV* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdWriteAccelerationStructuresPropertiesNV(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureNV* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBuildAccelerationStructureNV(VkCommandBuffer commandBuffer, const VkAccelerationStructureInfoNV* pInfo, VkBuffer instanceData, VkDeviceSize instanceOffset, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkBuffer scratch, VkDeviceSize scratchOffset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBuildAccelerationStructureNV(VkCommandBuffer commandBuffer, const VkAccelerationStructureInfoNV* pInfo, VkBuffer instanceData, VkDeviceSize instanceOffset, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkBuffer scratch, VkDeviceSize scratchOffset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBuildAccelerationStructureNV(VkCommandBuffer commandBuffer, const VkAccelerationStructureInfoNV* pInfo, VkBuffer instanceData, VkDeviceSize instanceOffset, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkBuffer scratch, VkDeviceSize scratchOffset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBuildAccelerationStructureNV(VkCommandBuffer commandBuffer, const VkAccelerationStructureInfoNV* pInfo, VkBuffer instanceData, VkDeviceSize instanceOffset, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkBuffer scratch, VkDeviceSize scratchOffset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBuildAccelerationStructureNV(VkCommandBuffer commandBuffer, const VkAccelerationStructureInfoNV* pInfo, VkBuffer instanceData, VkDeviceSize instanceOffset, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkBuffer scratch, VkDeviceSize scratchOffset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBuildAccelerationStructureNV(VkCommandBuffer commandBuffer, const VkAccelerationStructureInfoNV* pInfo, VkBuffer instanceData, VkDeviceSize instanceOffset, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkBuffer scratch, VkDeviceSize scratchOffset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBuildAccelerationStructureNV(VkCommandBuffer commandBuffer, const VkAccelerationStructureInfoNV* pInfo, VkBuffer instanceData, VkDeviceSize instanceOffset, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkBuffer scratch, VkDeviceSize scratchOffset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBuildAccelerationStructureNV(VkCommandBuffer commandBuffer, const VkAccelerationStructureInfoNV* pInfo, VkBuffer instanceData, VkDeviceSize instanceOffset, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkBuffer scratch, VkDeviceSize scratchOffset) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_WriteAccelerationStructuresPropertiesKHR(VkDevice device, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType  queryType, size_t       dataSize, void* pData, size_t stride) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_WriteAccelerationStructuresPropertiesKHR(VkDevice device, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType  queryType, size_t       dataSize, void* pData, size_t stride) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_WriteAccelerationStructuresPropertiesKHR(VkDevice device, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType  queryType, size_t       dataSize, void* pData, size_t stride) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_WriteAccelerationStructuresPropertiesKHR(VkDevice device, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType  queryType, size_t       dataSize, void* pData, size_t stride) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_WriteAccelerationStructuresPropertiesKHR(VkDevice device, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType  queryType, size_t       dataSize, void* pData, size_t stride) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_WriteAccelerationStructuresPropertiesKHR(VkDevice device, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType  queryType, size_t       dataSize, void* pData, size_t stride) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_WriteAccelerationStructuresPropertiesKHR(VkDevice device, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType  queryType, size_t       dataSize, void* pData, size_t stride) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_WriteAccelerationStructuresPropertiesKHR(VkDevice device, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType  queryType, size_t       dataSize, void* pData, size_t stride) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdTraceRaysKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdTraceRaysKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdTraceRaysKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdTraceRaysKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdTraceRaysKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdTraceRaysKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdTraceRaysKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdTraceRaysKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdTraceRaysNV(VkCommandBuffer commandBuffer, VkBuffer raygenShaderBindingTableBuffer, VkDeviceSize raygenShaderBindingOffset, VkBuffer missShaderBindingTableBuffer, VkDeviceSize missShaderBindingOffset, VkDeviceSize missShaderBindingStride, VkBuffer hitShaderBindingTableBuffer, VkDeviceSize hitShaderBindingOffset, VkDeviceSize hitShaderBindingStride, VkBuffer callableShaderBindingTableBuffer, VkDeviceSize callableShaderBindingOffset, VkDeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdTraceRaysNV(VkCommandBuffer commandBuffer, VkBuffer raygenShaderBindingTableBuffer, VkDeviceSize raygenShaderBindingOffset, VkBuffer missShaderBindingTableBuffer, VkDeviceSize missShaderBindingOffset, VkDeviceSize missShaderBindingStride, VkBuffer hitShaderBindingTableBuffer, VkDeviceSize hitShaderBindingOffset, VkDeviceSize hitShaderBindingStride, VkBuffer callableShaderBindingTableBuffer, VkDeviceSize callableShaderBindingOffset, VkDeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdTraceRaysNV(VkCommandBuffer commandBuffer, VkBuffer raygenShaderBindingTableBuffer, VkDeviceSize raygenShaderBindingOffset, VkBuffer missShaderBindingTableBuffer, VkDeviceSize missShaderBindingOffset, VkDeviceSize missShaderBindingStride, VkBuffer hitShaderBindingTableBuffer, VkDeviceSize hitShaderBindingOffset, VkDeviceSize hitShaderBindingStride, VkBuffer callableShaderBindingTableBuffer, VkDeviceSize callableShaderBindingOffset, VkDeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdTraceRaysNV(VkCommandBuffer commandBuffer, VkBuffer raygenShaderBindingTableBuffer, VkDeviceSize raygenShaderBindingOffset, VkBuffer missShaderBindingTableBuffer, VkDeviceSize missShaderBindingOffset, VkDeviceSize missShaderBindingStride, VkBuffer hitShaderBindingTableBuffer, VkDeviceSize hitShaderBindingOffset, VkDeviceSize hitShaderBindingStride, VkBuffer callableShaderBindingTableBuffer, VkDeviceSize callableShaderBindingOffset, VkDeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdTraceRaysNV(VkCommandBuffer commandBuffer, VkBuffer raygenShaderBindingTableBuffer, VkDeviceSize raygenShaderBindingOffset, VkBuffer missShaderBindingTableBuffer, VkDeviceSize missShaderBindingOffset, VkDeviceSize missShaderBindingStride, VkBuffer hitShaderBindingTableBuffer, VkDeviceSize hitShaderBindingOffset, VkDeviceSize hitShaderBindingStride, VkBuffer callableShaderBindingTableBuffer, VkDeviceSize callableShaderBindingOffset, VkDeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdTraceRaysNV(VkCommandBuffer commandBuffer, VkBuffer raygenShaderBindingTableBuffer, VkDeviceSize raygenShaderBindingOffset, VkBuffer missShaderBindingTableBuffer, VkDeviceSize missShaderBindingOffset, VkDeviceSize missShaderBindingStride, VkBuffer hitShaderBindingTableBuffer, VkDeviceSize hitShaderBindingOffset, VkDeviceSize hitShaderBindingStride, VkBuffer callableShaderBindingTableBuffer, VkDeviceSize callableShaderBindingOffset, VkDeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdTraceRaysNV(VkCommandBuffer commandBuffer, VkBuffer raygenShaderBindingTableBuffer, VkDeviceSize raygenShaderBindingOffset, VkBuffer missShaderBindingTableBuffer, VkDeviceSize missShaderBindingOffset, VkDeviceSize missShaderBindingStride, VkBuffer hitShaderBindingTableBuffer, VkDeviceSize hitShaderBindingOffset, VkDeviceSize hitShaderBindingStride, VkBuffer callableShaderBindingTableBuffer, VkDeviceSize callableShaderBindingOffset, VkDeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdTraceRaysNV(VkCommandBuffer commandBuffer, VkBuffer raygenShaderBindingTableBuffer, VkDeviceSize raygenShaderBindingOffset, VkBuffer missShaderBindingTableBuffer, VkDeviceSize missShaderBindingOffset, VkDeviceSize missShaderBindingStride, VkBuffer hitShaderBindingTableBuffer, VkDeviceSize hitShaderBindingOffset, VkDeviceSize hitShaderBindingStride, VkBuffer callableShaderBindingTableBuffer, VkDeviceSize callableShaderBindingOffset, VkDeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetRayTracingShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetRayTracingShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetRayTracingShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetRayTracingShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetRayTracingShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetRayTracingShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetRayTracingShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetRayTracingShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetRayTracingShaderGroupHandlesNV(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetRayTracingShaderGroupHandlesNV(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetRayTracingShaderGroupHandlesNV(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetRayTracingShaderGroupHandlesNV(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetRayTracingShaderGroupHandlesNV(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetRayTracingShaderGroupHandlesNV(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetRayTracingShaderGroupHandlesNV(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetRayTracingShaderGroupHandlesNV(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetRayTracingCaptureReplayShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetRayTracingCaptureReplayShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetRayTracingCaptureReplayShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetRayTracingCaptureReplayShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetRayTracingCaptureReplayShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetRayTracingCaptureReplayShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetRayTracingCaptureReplayShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetRayTracingCaptureReplayShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetAccelerationStructureHandleNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetAccelerationStructureHandleNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetAccelerationStructureHandleNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetAccelerationStructureHandleNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetAccelerationStructureHandleNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetAccelerationStructureHandleNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetAccelerationStructureHandleNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, size_t dataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetAccelerationStructureHandleNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, size_t dataSize, void* pData) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateRayTracingPipelinesNV(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoNV* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateRayTracingPipelinesNV(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoNV* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateRayTracingPipelinesNV(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoNV* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateRayTracingPipelinesNV(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoNV* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateRayTracingPipelinesNV(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoNV* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateRayTracingPipelinesNV(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoNV* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateRayTracingPipelinesNV(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoNV* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateRayTracingPipelinesNV(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoNV* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateRayTracingPipelinesKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateRayTracingPipelinesKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateRayTracingPipelinesKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateRayTracingPipelinesKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateRayTracingPipelinesKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateRayTracingPipelinesKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateRayTracingPipelinesKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateRayTracingPipelinesKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdTraceRaysIndirectKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, VkDeviceAddress indirectDeviceAddress) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdTraceRaysIndirectKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, VkDeviceAddress indirectDeviceAddress) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdTraceRaysIndirectKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, VkDeviceAddress indirectDeviceAddress) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdTraceRaysIndirectKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, VkDeviceAddress indirectDeviceAddress) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdTraceRaysIndirectKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, VkDeviceAddress indirectDeviceAddress) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdTraceRaysIndirectKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, VkDeviceAddress indirectDeviceAddress) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdTraceRaysIndirectKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, VkDeviceAddress indirectDeviceAddress) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdTraceRaysIndirectKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, VkDeviceAddress indirectDeviceAddress) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdTraceRaysIndirect2KHR(VkCommandBuffer commandBuffer, VkDeviceAddress indirectDeviceAddress) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdTraceRaysIndirect2KHR(VkCommandBuffer commandBuffer, VkDeviceAddress indirectDeviceAddress) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdTraceRaysIndirect2KHR(VkCommandBuffer commandBuffer, VkDeviceAddress indirectDeviceAddress) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdTraceRaysIndirect2KHR(VkCommandBuffer commandBuffer, VkDeviceAddress indirectDeviceAddress) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdTraceRaysIndirect2KHR(VkCommandBuffer commandBuffer, VkDeviceAddress indirectDeviceAddress) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdTraceRaysIndirect2KHR(VkCommandBuffer commandBuffer, VkDeviceAddress indirectDeviceAddress) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdTraceRaysIndirect2KHR(VkCommandBuffer commandBuffer, VkDeviceAddress indirectDeviceAddress) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdTraceRaysIndirect2KHR(VkCommandBuffer commandBuffer, VkDeviceAddress indirectDeviceAddress) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetDeviceAccelerationStructureCompatibilityKHR(VkDevice device, const VkAccelerationStructureVersionInfoKHR* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetDeviceAccelerationStructureCompatibilityKHR(VkDevice device, const VkAccelerationStructureVersionInfoKHR* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetDeviceAccelerationStructureCompatibilityKHR(VkDevice device, const VkAccelerationStructureVersionInfoKHR* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetDeviceAccelerationStructureCompatibilityKHR(VkDevice device, const VkAccelerationStructureVersionInfoKHR* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetDeviceAccelerationStructureCompatibilityKHR(VkDevice device, const VkAccelerationStructureVersionInfoKHR* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetDeviceAccelerationStructureCompatibilityKHR(VkDevice device, const VkAccelerationStructureVersionInfoKHR* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetDeviceAccelerationStructureCompatibilityKHR(VkDevice device, const VkAccelerationStructureVersionInfoKHR* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetDeviceAccelerationStructureCompatibilityKHR(VkDevice device, const VkAccelerationStructureVersionInfoKHR* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility) ATTR_WEAK;


  VKAPI_ATTR VkDeviceSize VKAPI_CALL anv_GetRayTracingShaderGroupStackSizeKHR(VkDevice device, VkPipeline pipeline, uint32_t group, VkShaderGroupShaderKHR groupShader) ATTR_WEAK;
  VKAPI_ATTR VkDeviceSize VKAPI_CALL gfx9_GetRayTracingShaderGroupStackSizeKHR(VkDevice device, VkPipeline pipeline, uint32_t group, VkShaderGroupShaderKHR groupShader) ATTR_WEAK;
  VKAPI_ATTR VkDeviceSize VKAPI_CALL gfx11_GetRayTracingShaderGroupStackSizeKHR(VkDevice device, VkPipeline pipeline, uint32_t group, VkShaderGroupShaderKHR groupShader) ATTR_WEAK;
  VKAPI_ATTR VkDeviceSize VKAPI_CALL gfx12_GetRayTracingShaderGroupStackSizeKHR(VkDevice device, VkPipeline pipeline, uint32_t group, VkShaderGroupShaderKHR groupShader) ATTR_WEAK;
  VKAPI_ATTR VkDeviceSize VKAPI_CALL gfx125_GetRayTracingShaderGroupStackSizeKHR(VkDevice device, VkPipeline pipeline, uint32_t group, VkShaderGroupShaderKHR groupShader) ATTR_WEAK;
  VKAPI_ATTR VkDeviceSize VKAPI_CALL doom64_GetRayTracingShaderGroupStackSizeKHR(VkDevice device, VkPipeline pipeline, uint32_t group, VkShaderGroupShaderKHR groupShader) ATTR_WEAK;
  VKAPI_ATTR VkDeviceSize VKAPI_CALL hitman3_GetRayTracingShaderGroupStackSizeKHR(VkDevice device, VkPipeline pipeline, uint32_t group, VkShaderGroupShaderKHR groupShader) ATTR_WEAK;
  VKAPI_ATTR VkDeviceSize VKAPI_CALL android_GetRayTracingShaderGroupStackSizeKHR(VkDevice device, VkPipeline pipeline, uint32_t group, VkShaderGroupShaderKHR groupShader) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetRayTracingPipelineStackSizeKHR(VkCommandBuffer commandBuffer, uint32_t pipelineStackSize) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetRayTracingPipelineStackSizeKHR(VkCommandBuffer commandBuffer, uint32_t pipelineStackSize) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetRayTracingPipelineStackSizeKHR(VkCommandBuffer commandBuffer, uint32_t pipelineStackSize) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetRayTracingPipelineStackSizeKHR(VkCommandBuffer commandBuffer, uint32_t pipelineStackSize) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetRayTracingPipelineStackSizeKHR(VkCommandBuffer commandBuffer, uint32_t pipelineStackSize) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetRayTracingPipelineStackSizeKHR(VkCommandBuffer commandBuffer, uint32_t pipelineStackSize) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetRayTracingPipelineStackSizeKHR(VkCommandBuffer commandBuffer, uint32_t pipelineStackSize) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetRayTracingPipelineStackSizeKHR(VkCommandBuffer commandBuffer, uint32_t pipelineStackSize) ATTR_WEAK;


  VKAPI_ATTR uint32_t VKAPI_CALL anv_GetImageViewHandleNVX(VkDevice device, const VkImageViewHandleInfoNVX* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint32_t VKAPI_CALL gfx9_GetImageViewHandleNVX(VkDevice device, const VkImageViewHandleInfoNVX* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint32_t VKAPI_CALL gfx11_GetImageViewHandleNVX(VkDevice device, const VkImageViewHandleInfoNVX* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint32_t VKAPI_CALL gfx12_GetImageViewHandleNVX(VkDevice device, const VkImageViewHandleInfoNVX* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint32_t VKAPI_CALL gfx125_GetImageViewHandleNVX(VkDevice device, const VkImageViewHandleInfoNVX* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint32_t VKAPI_CALL doom64_GetImageViewHandleNVX(VkDevice device, const VkImageViewHandleInfoNVX* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint32_t VKAPI_CALL hitman3_GetImageViewHandleNVX(VkDevice device, const VkImageViewHandleInfoNVX* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint32_t VKAPI_CALL android_GetImageViewHandleNVX(VkDevice device, const VkImageViewHandleInfoNVX* pInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetImageViewAddressNVX(VkDevice device, VkImageView imageView, VkImageViewAddressPropertiesNVX* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetImageViewAddressNVX(VkDevice device, VkImageView imageView, VkImageViewAddressPropertiesNVX* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetImageViewAddressNVX(VkDevice device, VkImageView imageView, VkImageViewAddressPropertiesNVX* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetImageViewAddressNVX(VkDevice device, VkImageView imageView, VkImageViewAddressPropertiesNVX* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetImageViewAddressNVX(VkDevice device, VkImageView imageView, VkImageViewAddressPropertiesNVX* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetImageViewAddressNVX(VkDevice device, VkImageView imageView, VkImageViewAddressPropertiesNVX* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetImageViewAddressNVX(VkDevice device, VkImageView imageView, VkImageViewAddressPropertiesNVX* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetImageViewAddressNVX(VkDevice device, VkImageView imageView, VkImageViewAddressPropertiesNVX* pProperties) ATTR_WEAK;


#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetDeviceGroupSurfacePresentModes2EXT(VkDevice device, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkDeviceGroupPresentModeFlagsKHR* pModes) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetDeviceGroupSurfacePresentModes2EXT(VkDevice device, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkDeviceGroupPresentModeFlagsKHR* pModes) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetDeviceGroupSurfacePresentModes2EXT(VkDevice device, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkDeviceGroupPresentModeFlagsKHR* pModes) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetDeviceGroupSurfacePresentModes2EXT(VkDevice device, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkDeviceGroupPresentModeFlagsKHR* pModes) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetDeviceGroupSurfacePresentModes2EXT(VkDevice device, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkDeviceGroupPresentModeFlagsKHR* pModes) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetDeviceGroupSurfacePresentModes2EXT(VkDevice device, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkDeviceGroupPresentModeFlagsKHR* pModes) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetDeviceGroupSurfacePresentModes2EXT(VkDevice device, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkDeviceGroupPresentModeFlagsKHR* pModes) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetDeviceGroupSurfacePresentModes2EXT(VkDevice device, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkDeviceGroupPresentModeFlagsKHR* pModes) ATTR_WEAK;


#endif // VK_USE_PLATFORM_WIN32_KHR
#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_AcquireFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_AcquireFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_AcquireFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_AcquireFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_AcquireFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_AcquireFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_AcquireFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_AcquireFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;


#endif // VK_USE_PLATFORM_WIN32_KHR
#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_ReleaseFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_ReleaseFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_ReleaseFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_ReleaseFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_ReleaseFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_ReleaseFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_ReleaseFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_ReleaseFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain) ATTR_WEAK;


#endif // VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL anv_AcquireProfilingLockKHR(VkDevice device, const VkAcquireProfilingLockInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_AcquireProfilingLockKHR(VkDevice device, const VkAcquireProfilingLockInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_AcquireProfilingLockKHR(VkDevice device, const VkAcquireProfilingLockInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_AcquireProfilingLockKHR(VkDevice device, const VkAcquireProfilingLockInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_AcquireProfilingLockKHR(VkDevice device, const VkAcquireProfilingLockInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_AcquireProfilingLockKHR(VkDevice device, const VkAcquireProfilingLockInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_AcquireProfilingLockKHR(VkDevice device, const VkAcquireProfilingLockInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_AcquireProfilingLockKHR(VkDevice device, const VkAcquireProfilingLockInfoKHR* pInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_ReleaseProfilingLockKHR(VkDevice device) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_ReleaseProfilingLockKHR(VkDevice device) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_ReleaseProfilingLockKHR(VkDevice device) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_ReleaseProfilingLockKHR(VkDevice device) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_ReleaseProfilingLockKHR(VkDevice device) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_ReleaseProfilingLockKHR(VkDevice device) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_ReleaseProfilingLockKHR(VkDevice device) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_ReleaseProfilingLockKHR(VkDevice device) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetImageDrmFormatModifierPropertiesEXT(VkDevice device, VkImage image, VkImageDrmFormatModifierPropertiesEXT* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetImageDrmFormatModifierPropertiesEXT(VkDevice device, VkImage image, VkImageDrmFormatModifierPropertiesEXT* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetImageDrmFormatModifierPropertiesEXT(VkDevice device, VkImage image, VkImageDrmFormatModifierPropertiesEXT* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetImageDrmFormatModifierPropertiesEXT(VkDevice device, VkImage image, VkImageDrmFormatModifierPropertiesEXT* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetImageDrmFormatModifierPropertiesEXT(VkDevice device, VkImage image, VkImageDrmFormatModifierPropertiesEXT* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetImageDrmFormatModifierPropertiesEXT(VkDevice device, VkImage image, VkImageDrmFormatModifierPropertiesEXT* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetImageDrmFormatModifierPropertiesEXT(VkDevice device, VkImage image, VkImageDrmFormatModifierPropertiesEXT* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetImageDrmFormatModifierPropertiesEXT(VkDevice device, VkImage image, VkImageDrmFormatModifierPropertiesEXT* pProperties) ATTR_WEAK;


  VKAPI_ATTR uint64_t VKAPI_CALL anv_GetBufferOpaqueCaptureAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL gfx9_GetBufferOpaqueCaptureAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL gfx11_GetBufferOpaqueCaptureAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL gfx12_GetBufferOpaqueCaptureAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL gfx125_GetBufferOpaqueCaptureAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL doom64_GetBufferOpaqueCaptureAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL hitman3_GetBufferOpaqueCaptureAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL android_GetBufferOpaqueCaptureAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;


  VKAPI_ATTR uint64_t VKAPI_CALL anv_GetBufferOpaqueCaptureAddressKHR(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL gfx9_GetBufferOpaqueCaptureAddressKHR(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL gfx11_GetBufferOpaqueCaptureAddressKHR(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL gfx12_GetBufferOpaqueCaptureAddressKHR(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL gfx125_GetBufferOpaqueCaptureAddressKHR(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL doom64_GetBufferOpaqueCaptureAddressKHR(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL hitman3_GetBufferOpaqueCaptureAddressKHR(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL android_GetBufferOpaqueCaptureAddressKHR(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;


  VKAPI_ATTR VkDeviceAddress VKAPI_CALL anv_GetBufferDeviceAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL gfx9_GetBufferDeviceAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL gfx11_GetBufferDeviceAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL gfx12_GetBufferDeviceAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL gfx125_GetBufferDeviceAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL doom64_GetBufferDeviceAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL hitman3_GetBufferDeviceAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL android_GetBufferDeviceAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;


  VKAPI_ATTR VkDeviceAddress VKAPI_CALL anv_GetBufferDeviceAddressKHR(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL gfx9_GetBufferDeviceAddressKHR(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL gfx11_GetBufferDeviceAddressKHR(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL gfx12_GetBufferDeviceAddressKHR(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL gfx125_GetBufferDeviceAddressKHR(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL doom64_GetBufferDeviceAddressKHR(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL hitman3_GetBufferDeviceAddressKHR(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL android_GetBufferDeviceAddressKHR(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;


  VKAPI_ATTR VkDeviceAddress VKAPI_CALL anv_GetBufferDeviceAddressEXT(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL gfx9_GetBufferDeviceAddressEXT(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL gfx11_GetBufferDeviceAddressEXT(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL gfx12_GetBufferDeviceAddressEXT(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL gfx125_GetBufferDeviceAddressEXT(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL doom64_GetBufferDeviceAddressEXT(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL hitman3_GetBufferDeviceAddressEXT(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL android_GetBufferDeviceAddressEXT(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_InitializePerformanceApiINTEL(VkDevice device, const VkInitializePerformanceApiInfoINTEL* pInitializeInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_InitializePerformanceApiINTEL(VkDevice device, const VkInitializePerformanceApiInfoINTEL* pInitializeInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_InitializePerformanceApiINTEL(VkDevice device, const VkInitializePerformanceApiInfoINTEL* pInitializeInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_InitializePerformanceApiINTEL(VkDevice device, const VkInitializePerformanceApiInfoINTEL* pInitializeInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_InitializePerformanceApiINTEL(VkDevice device, const VkInitializePerformanceApiInfoINTEL* pInitializeInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_InitializePerformanceApiINTEL(VkDevice device, const VkInitializePerformanceApiInfoINTEL* pInitializeInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_InitializePerformanceApiINTEL(VkDevice device, const VkInitializePerformanceApiInfoINTEL* pInitializeInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_InitializePerformanceApiINTEL(VkDevice device, const VkInitializePerformanceApiInfoINTEL* pInitializeInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_UninitializePerformanceApiINTEL(VkDevice device) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_UninitializePerformanceApiINTEL(VkDevice device) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_UninitializePerformanceApiINTEL(VkDevice device) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_UninitializePerformanceApiINTEL(VkDevice device) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_UninitializePerformanceApiINTEL(VkDevice device) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_UninitializePerformanceApiINTEL(VkDevice device) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_UninitializePerformanceApiINTEL(VkDevice device) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_UninitializePerformanceApiINTEL(VkDevice device) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CmdSetPerformanceMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceMarkerInfoINTEL* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CmdSetPerformanceMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceMarkerInfoINTEL* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CmdSetPerformanceMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceMarkerInfoINTEL* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CmdSetPerformanceMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceMarkerInfoINTEL* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CmdSetPerformanceMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceMarkerInfoINTEL* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CmdSetPerformanceMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceMarkerInfoINTEL* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CmdSetPerformanceMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceMarkerInfoINTEL* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CmdSetPerformanceMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceMarkerInfoINTEL* pMarkerInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CmdSetPerformanceStreamMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceStreamMarkerInfoINTEL* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CmdSetPerformanceStreamMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceStreamMarkerInfoINTEL* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CmdSetPerformanceStreamMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceStreamMarkerInfoINTEL* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CmdSetPerformanceStreamMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceStreamMarkerInfoINTEL* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CmdSetPerformanceStreamMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceStreamMarkerInfoINTEL* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CmdSetPerformanceStreamMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceStreamMarkerInfoINTEL* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CmdSetPerformanceStreamMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceStreamMarkerInfoINTEL* pMarkerInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CmdSetPerformanceStreamMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceStreamMarkerInfoINTEL* pMarkerInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CmdSetPerformanceOverrideINTEL(VkCommandBuffer commandBuffer, const VkPerformanceOverrideInfoINTEL* pOverrideInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CmdSetPerformanceOverrideINTEL(VkCommandBuffer commandBuffer, const VkPerformanceOverrideInfoINTEL* pOverrideInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CmdSetPerformanceOverrideINTEL(VkCommandBuffer commandBuffer, const VkPerformanceOverrideInfoINTEL* pOverrideInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CmdSetPerformanceOverrideINTEL(VkCommandBuffer commandBuffer, const VkPerformanceOverrideInfoINTEL* pOverrideInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CmdSetPerformanceOverrideINTEL(VkCommandBuffer commandBuffer, const VkPerformanceOverrideInfoINTEL* pOverrideInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CmdSetPerformanceOverrideINTEL(VkCommandBuffer commandBuffer, const VkPerformanceOverrideInfoINTEL* pOverrideInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CmdSetPerformanceOverrideINTEL(VkCommandBuffer commandBuffer, const VkPerformanceOverrideInfoINTEL* pOverrideInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CmdSetPerformanceOverrideINTEL(VkCommandBuffer commandBuffer, const VkPerformanceOverrideInfoINTEL* pOverrideInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_AcquirePerformanceConfigurationINTEL(VkDevice device, const VkPerformanceConfigurationAcquireInfoINTEL* pAcquireInfo, VkPerformanceConfigurationINTEL* pConfiguration) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_AcquirePerformanceConfigurationINTEL(VkDevice device, const VkPerformanceConfigurationAcquireInfoINTEL* pAcquireInfo, VkPerformanceConfigurationINTEL* pConfiguration) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_AcquirePerformanceConfigurationINTEL(VkDevice device, const VkPerformanceConfigurationAcquireInfoINTEL* pAcquireInfo, VkPerformanceConfigurationINTEL* pConfiguration) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_AcquirePerformanceConfigurationINTEL(VkDevice device, const VkPerformanceConfigurationAcquireInfoINTEL* pAcquireInfo, VkPerformanceConfigurationINTEL* pConfiguration) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_AcquirePerformanceConfigurationINTEL(VkDevice device, const VkPerformanceConfigurationAcquireInfoINTEL* pAcquireInfo, VkPerformanceConfigurationINTEL* pConfiguration) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_AcquirePerformanceConfigurationINTEL(VkDevice device, const VkPerformanceConfigurationAcquireInfoINTEL* pAcquireInfo, VkPerformanceConfigurationINTEL* pConfiguration) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_AcquirePerformanceConfigurationINTEL(VkDevice device, const VkPerformanceConfigurationAcquireInfoINTEL* pAcquireInfo, VkPerformanceConfigurationINTEL* pConfiguration) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_AcquirePerformanceConfigurationINTEL(VkDevice device, const VkPerformanceConfigurationAcquireInfoINTEL* pAcquireInfo, VkPerformanceConfigurationINTEL* pConfiguration) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_ReleasePerformanceConfigurationINTEL(VkDevice device, VkPerformanceConfigurationINTEL configuration) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_ReleasePerformanceConfigurationINTEL(VkDevice device, VkPerformanceConfigurationINTEL configuration) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_ReleasePerformanceConfigurationINTEL(VkDevice device, VkPerformanceConfigurationINTEL configuration) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_ReleasePerformanceConfigurationINTEL(VkDevice device, VkPerformanceConfigurationINTEL configuration) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_ReleasePerformanceConfigurationINTEL(VkDevice device, VkPerformanceConfigurationINTEL configuration) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_ReleasePerformanceConfigurationINTEL(VkDevice device, VkPerformanceConfigurationINTEL configuration) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_ReleasePerformanceConfigurationINTEL(VkDevice device, VkPerformanceConfigurationINTEL configuration) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_ReleasePerformanceConfigurationINTEL(VkDevice device, VkPerformanceConfigurationINTEL configuration) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_QueueSetPerformanceConfigurationINTEL(VkQueue queue, VkPerformanceConfigurationINTEL configuration) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_QueueSetPerformanceConfigurationINTEL(VkQueue queue, VkPerformanceConfigurationINTEL configuration) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_QueueSetPerformanceConfigurationINTEL(VkQueue queue, VkPerformanceConfigurationINTEL configuration) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_QueueSetPerformanceConfigurationINTEL(VkQueue queue, VkPerformanceConfigurationINTEL configuration) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_QueueSetPerformanceConfigurationINTEL(VkQueue queue, VkPerformanceConfigurationINTEL configuration) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_QueueSetPerformanceConfigurationINTEL(VkQueue queue, VkPerformanceConfigurationINTEL configuration) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_QueueSetPerformanceConfigurationINTEL(VkQueue queue, VkPerformanceConfigurationINTEL configuration) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_QueueSetPerformanceConfigurationINTEL(VkQueue queue, VkPerformanceConfigurationINTEL configuration) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPerformanceParameterINTEL(VkDevice device, VkPerformanceParameterTypeINTEL parameter, VkPerformanceValueINTEL* pValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetPerformanceParameterINTEL(VkDevice device, VkPerformanceParameterTypeINTEL parameter, VkPerformanceValueINTEL* pValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetPerformanceParameterINTEL(VkDevice device, VkPerformanceParameterTypeINTEL parameter, VkPerformanceValueINTEL* pValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetPerformanceParameterINTEL(VkDevice device, VkPerformanceParameterTypeINTEL parameter, VkPerformanceValueINTEL* pValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetPerformanceParameterINTEL(VkDevice device, VkPerformanceParameterTypeINTEL parameter, VkPerformanceValueINTEL* pValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetPerformanceParameterINTEL(VkDevice device, VkPerformanceParameterTypeINTEL parameter, VkPerformanceValueINTEL* pValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetPerformanceParameterINTEL(VkDevice device, VkPerformanceParameterTypeINTEL parameter, VkPerformanceValueINTEL* pValue) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetPerformanceParameterINTEL(VkDevice device, VkPerformanceParameterTypeINTEL parameter, VkPerformanceValueINTEL* pValue) ATTR_WEAK;


  VKAPI_ATTR uint64_t VKAPI_CALL anv_GetDeviceMemoryOpaqueCaptureAddress(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL gfx9_GetDeviceMemoryOpaqueCaptureAddress(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL gfx11_GetDeviceMemoryOpaqueCaptureAddress(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL gfx12_GetDeviceMemoryOpaqueCaptureAddress(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL gfx125_GetDeviceMemoryOpaqueCaptureAddress(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL doom64_GetDeviceMemoryOpaqueCaptureAddress(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL hitman3_GetDeviceMemoryOpaqueCaptureAddress(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL android_GetDeviceMemoryOpaqueCaptureAddress(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) ATTR_WEAK;


  VKAPI_ATTR uint64_t VKAPI_CALL anv_GetDeviceMemoryOpaqueCaptureAddressKHR(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL gfx9_GetDeviceMemoryOpaqueCaptureAddressKHR(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL gfx11_GetDeviceMemoryOpaqueCaptureAddressKHR(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL gfx12_GetDeviceMemoryOpaqueCaptureAddressKHR(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL gfx125_GetDeviceMemoryOpaqueCaptureAddressKHR(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL doom64_GetDeviceMemoryOpaqueCaptureAddressKHR(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL hitman3_GetDeviceMemoryOpaqueCaptureAddressKHR(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) ATTR_WEAK;
  VKAPI_ATTR uint64_t VKAPI_CALL android_GetDeviceMemoryOpaqueCaptureAddressKHR(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPipelineExecutablePropertiesKHR(VkDevice                        device, const VkPipelineInfoKHR*        pPipelineInfo, uint32_t* pExecutableCount, VkPipelineExecutablePropertiesKHR* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetPipelineExecutablePropertiesKHR(VkDevice                        device, const VkPipelineInfoKHR*        pPipelineInfo, uint32_t* pExecutableCount, VkPipelineExecutablePropertiesKHR* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetPipelineExecutablePropertiesKHR(VkDevice                        device, const VkPipelineInfoKHR*        pPipelineInfo, uint32_t* pExecutableCount, VkPipelineExecutablePropertiesKHR* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetPipelineExecutablePropertiesKHR(VkDevice                        device, const VkPipelineInfoKHR*        pPipelineInfo, uint32_t* pExecutableCount, VkPipelineExecutablePropertiesKHR* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetPipelineExecutablePropertiesKHR(VkDevice                        device, const VkPipelineInfoKHR*        pPipelineInfo, uint32_t* pExecutableCount, VkPipelineExecutablePropertiesKHR* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetPipelineExecutablePropertiesKHR(VkDevice                        device, const VkPipelineInfoKHR*        pPipelineInfo, uint32_t* pExecutableCount, VkPipelineExecutablePropertiesKHR* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetPipelineExecutablePropertiesKHR(VkDevice                        device, const VkPipelineInfoKHR*        pPipelineInfo, uint32_t* pExecutableCount, VkPipelineExecutablePropertiesKHR* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetPipelineExecutablePropertiesKHR(VkDevice                        device, const VkPipelineInfoKHR*        pPipelineInfo, uint32_t* pExecutableCount, VkPipelineExecutablePropertiesKHR* pProperties) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPipelineExecutableStatisticsKHR(VkDevice                        device, const VkPipelineExecutableInfoKHR*  pExecutableInfo, uint32_t* pStatisticCount, VkPipelineExecutableStatisticKHR* pStatistics) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetPipelineExecutableStatisticsKHR(VkDevice                        device, const VkPipelineExecutableInfoKHR*  pExecutableInfo, uint32_t* pStatisticCount, VkPipelineExecutableStatisticKHR* pStatistics) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetPipelineExecutableStatisticsKHR(VkDevice                        device, const VkPipelineExecutableInfoKHR*  pExecutableInfo, uint32_t* pStatisticCount, VkPipelineExecutableStatisticKHR* pStatistics) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetPipelineExecutableStatisticsKHR(VkDevice                        device, const VkPipelineExecutableInfoKHR*  pExecutableInfo, uint32_t* pStatisticCount, VkPipelineExecutableStatisticKHR* pStatistics) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetPipelineExecutableStatisticsKHR(VkDevice                        device, const VkPipelineExecutableInfoKHR*  pExecutableInfo, uint32_t* pStatisticCount, VkPipelineExecutableStatisticKHR* pStatistics) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetPipelineExecutableStatisticsKHR(VkDevice                        device, const VkPipelineExecutableInfoKHR*  pExecutableInfo, uint32_t* pStatisticCount, VkPipelineExecutableStatisticKHR* pStatistics) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetPipelineExecutableStatisticsKHR(VkDevice                        device, const VkPipelineExecutableInfoKHR*  pExecutableInfo, uint32_t* pStatisticCount, VkPipelineExecutableStatisticKHR* pStatistics) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetPipelineExecutableStatisticsKHR(VkDevice                        device, const VkPipelineExecutableInfoKHR*  pExecutableInfo, uint32_t* pStatisticCount, VkPipelineExecutableStatisticKHR* pStatistics) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPipelineExecutableInternalRepresentationsKHR(VkDevice                        device, const VkPipelineExecutableInfoKHR*  pExecutableInfo, uint32_t* pInternalRepresentationCount, VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetPipelineExecutableInternalRepresentationsKHR(VkDevice                        device, const VkPipelineExecutableInfoKHR*  pExecutableInfo, uint32_t* pInternalRepresentationCount, VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetPipelineExecutableInternalRepresentationsKHR(VkDevice                        device, const VkPipelineExecutableInfoKHR*  pExecutableInfo, uint32_t* pInternalRepresentationCount, VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetPipelineExecutableInternalRepresentationsKHR(VkDevice                        device, const VkPipelineExecutableInfoKHR*  pExecutableInfo, uint32_t* pInternalRepresentationCount, VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetPipelineExecutableInternalRepresentationsKHR(VkDevice                        device, const VkPipelineExecutableInfoKHR*  pExecutableInfo, uint32_t* pInternalRepresentationCount, VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetPipelineExecutableInternalRepresentationsKHR(VkDevice                        device, const VkPipelineExecutableInfoKHR*  pExecutableInfo, uint32_t* pInternalRepresentationCount, VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetPipelineExecutableInternalRepresentationsKHR(VkDevice                        device, const VkPipelineExecutableInfoKHR*  pExecutableInfo, uint32_t* pInternalRepresentationCount, VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetPipelineExecutableInternalRepresentationsKHR(VkDevice                        device, const VkPipelineExecutableInfoKHR*  pExecutableInfo, uint32_t* pInternalRepresentationCount, VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetLineStippleEXT(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetLineStippleEXT(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetLineStippleEXT(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetLineStippleEXT(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetLineStippleEXT(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetLineStippleEXT(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetLineStippleEXT(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetLineStippleEXT(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateAccelerationStructureKHR(VkDevice                                           device, const VkAccelerationStructureCreateInfoKHR*        pCreateInfo, const VkAllocationCallbacks*       pAllocator, VkAccelerationStructureKHR*                        pAccelerationStructure) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateAccelerationStructureKHR(VkDevice                                           device, const VkAccelerationStructureCreateInfoKHR*        pCreateInfo, const VkAllocationCallbacks*       pAllocator, VkAccelerationStructureKHR*                        pAccelerationStructure) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateAccelerationStructureKHR(VkDevice                                           device, const VkAccelerationStructureCreateInfoKHR*        pCreateInfo, const VkAllocationCallbacks*       pAllocator, VkAccelerationStructureKHR*                        pAccelerationStructure) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateAccelerationStructureKHR(VkDevice                                           device, const VkAccelerationStructureCreateInfoKHR*        pCreateInfo, const VkAllocationCallbacks*       pAllocator, VkAccelerationStructureKHR*                        pAccelerationStructure) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateAccelerationStructureKHR(VkDevice                                           device, const VkAccelerationStructureCreateInfoKHR*        pCreateInfo, const VkAllocationCallbacks*       pAllocator, VkAccelerationStructureKHR*                        pAccelerationStructure) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateAccelerationStructureKHR(VkDevice                                           device, const VkAccelerationStructureCreateInfoKHR*        pCreateInfo, const VkAllocationCallbacks*       pAllocator, VkAccelerationStructureKHR*                        pAccelerationStructure) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateAccelerationStructureKHR(VkDevice                                           device, const VkAccelerationStructureCreateInfoKHR*        pCreateInfo, const VkAllocationCallbacks*       pAllocator, VkAccelerationStructureKHR*                        pAccelerationStructure) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateAccelerationStructureKHR(VkDevice                                           device, const VkAccelerationStructureCreateInfoKHR*        pCreateInfo, const VkAllocationCallbacks*       pAllocator, VkAccelerationStructureKHR*                        pAccelerationStructure) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBuildAccelerationStructuresKHR(VkCommandBuffer                                    commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBuildAccelerationStructuresKHR(VkCommandBuffer                                    commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBuildAccelerationStructuresKHR(VkCommandBuffer                                    commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBuildAccelerationStructuresKHR(VkCommandBuffer                                    commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBuildAccelerationStructuresKHR(VkCommandBuffer                                    commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBuildAccelerationStructuresKHR(VkCommandBuffer                                    commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBuildAccelerationStructuresKHR(VkCommandBuffer                                    commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBuildAccelerationStructuresKHR(VkCommandBuffer                                    commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBuildAccelerationStructuresIndirectKHR(VkCommandBuffer                  commandBuffer, uint32_t                                           infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkDeviceAddress*             pIndirectDeviceAddresses, const uint32_t*                    pIndirectStrides, const uint32_t* const*             ppMaxPrimitiveCounts) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBuildAccelerationStructuresIndirectKHR(VkCommandBuffer                  commandBuffer, uint32_t                                           infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkDeviceAddress*             pIndirectDeviceAddresses, const uint32_t*                    pIndirectStrides, const uint32_t* const*             ppMaxPrimitiveCounts) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBuildAccelerationStructuresIndirectKHR(VkCommandBuffer                  commandBuffer, uint32_t                                           infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkDeviceAddress*             pIndirectDeviceAddresses, const uint32_t*                    pIndirectStrides, const uint32_t* const*             ppMaxPrimitiveCounts) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBuildAccelerationStructuresIndirectKHR(VkCommandBuffer                  commandBuffer, uint32_t                                           infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkDeviceAddress*             pIndirectDeviceAddresses, const uint32_t*                    pIndirectStrides, const uint32_t* const*             ppMaxPrimitiveCounts) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBuildAccelerationStructuresIndirectKHR(VkCommandBuffer                  commandBuffer, uint32_t                                           infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkDeviceAddress*             pIndirectDeviceAddresses, const uint32_t*                    pIndirectStrides, const uint32_t* const*             ppMaxPrimitiveCounts) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBuildAccelerationStructuresIndirectKHR(VkCommandBuffer                  commandBuffer, uint32_t                                           infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkDeviceAddress*             pIndirectDeviceAddresses, const uint32_t*                    pIndirectStrides, const uint32_t* const*             ppMaxPrimitiveCounts) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBuildAccelerationStructuresIndirectKHR(VkCommandBuffer                  commandBuffer, uint32_t                                           infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkDeviceAddress*             pIndirectDeviceAddresses, const uint32_t*                    pIndirectStrides, const uint32_t* const*             ppMaxPrimitiveCounts) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBuildAccelerationStructuresIndirectKHR(VkCommandBuffer                  commandBuffer, uint32_t                                           infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkDeviceAddress*             pIndirectDeviceAddresses, const uint32_t*                    pIndirectStrides, const uint32_t* const*             ppMaxPrimitiveCounts) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_BuildAccelerationStructuresKHR(VkDevice                                           device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_BuildAccelerationStructuresKHR(VkDevice                                           device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_BuildAccelerationStructuresKHR(VkDevice                                           device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_BuildAccelerationStructuresKHR(VkDevice                                           device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_BuildAccelerationStructuresKHR(VkDevice                                           device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_BuildAccelerationStructuresKHR(VkDevice                                           device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_BuildAccelerationStructuresKHR(VkDevice                                           device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_BuildAccelerationStructuresKHR(VkDevice                                           device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) ATTR_WEAK;


  VKAPI_ATTR VkDeviceAddress VKAPI_CALL anv_GetAccelerationStructureDeviceAddressKHR(VkDevice device, const VkAccelerationStructureDeviceAddressInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL gfx9_GetAccelerationStructureDeviceAddressKHR(VkDevice device, const VkAccelerationStructureDeviceAddressInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL gfx11_GetAccelerationStructureDeviceAddressKHR(VkDevice device, const VkAccelerationStructureDeviceAddressInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL gfx12_GetAccelerationStructureDeviceAddressKHR(VkDevice device, const VkAccelerationStructureDeviceAddressInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL gfx125_GetAccelerationStructureDeviceAddressKHR(VkDevice device, const VkAccelerationStructureDeviceAddressInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL doom64_GetAccelerationStructureDeviceAddressKHR(VkDevice device, const VkAccelerationStructureDeviceAddressInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL hitman3_GetAccelerationStructureDeviceAddressKHR(VkDevice device, const VkAccelerationStructureDeviceAddressInfoKHR* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL android_GetAccelerationStructureDeviceAddressKHR(VkDevice device, const VkAccelerationStructureDeviceAddressInfoKHR* pInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateDeferredOperationKHR(VkDevice device, const VkAllocationCallbacks* pAllocator, VkDeferredOperationKHR* pDeferredOperation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateDeferredOperationKHR(VkDevice device, const VkAllocationCallbacks* pAllocator, VkDeferredOperationKHR* pDeferredOperation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateDeferredOperationKHR(VkDevice device, const VkAllocationCallbacks* pAllocator, VkDeferredOperationKHR* pDeferredOperation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateDeferredOperationKHR(VkDevice device, const VkAllocationCallbacks* pAllocator, VkDeferredOperationKHR* pDeferredOperation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateDeferredOperationKHR(VkDevice device, const VkAllocationCallbacks* pAllocator, VkDeferredOperationKHR* pDeferredOperation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateDeferredOperationKHR(VkDevice device, const VkAllocationCallbacks* pAllocator, VkDeferredOperationKHR* pDeferredOperation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateDeferredOperationKHR(VkDevice device, const VkAllocationCallbacks* pAllocator, VkDeferredOperationKHR* pDeferredOperation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateDeferredOperationKHR(VkDevice device, const VkAllocationCallbacks* pAllocator, VkDeferredOperationKHR* pDeferredOperation) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyDeferredOperationKHR(VkDevice device, VkDeferredOperationKHR operation, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyDeferredOperationKHR(VkDevice device, VkDeferredOperationKHR operation, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyDeferredOperationKHR(VkDevice device, VkDeferredOperationKHR operation, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyDeferredOperationKHR(VkDevice device, VkDeferredOperationKHR operation, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyDeferredOperationKHR(VkDevice device, VkDeferredOperationKHR operation, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyDeferredOperationKHR(VkDevice device, VkDeferredOperationKHR operation, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyDeferredOperationKHR(VkDevice device, VkDeferredOperationKHR operation, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyDeferredOperationKHR(VkDevice device, VkDeferredOperationKHR operation, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR uint32_t VKAPI_CALL anv_GetDeferredOperationMaxConcurrencyKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;
  VKAPI_ATTR uint32_t VKAPI_CALL gfx9_GetDeferredOperationMaxConcurrencyKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;
  VKAPI_ATTR uint32_t VKAPI_CALL gfx11_GetDeferredOperationMaxConcurrencyKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;
  VKAPI_ATTR uint32_t VKAPI_CALL gfx12_GetDeferredOperationMaxConcurrencyKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;
  VKAPI_ATTR uint32_t VKAPI_CALL gfx125_GetDeferredOperationMaxConcurrencyKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;
  VKAPI_ATTR uint32_t VKAPI_CALL doom64_GetDeferredOperationMaxConcurrencyKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;
  VKAPI_ATTR uint32_t VKAPI_CALL hitman3_GetDeferredOperationMaxConcurrencyKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;
  VKAPI_ATTR uint32_t VKAPI_CALL android_GetDeferredOperationMaxConcurrencyKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetDeferredOperationResultKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetDeferredOperationResultKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetDeferredOperationResultKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetDeferredOperationResultKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetDeferredOperationResultKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetDeferredOperationResultKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetDeferredOperationResultKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetDeferredOperationResultKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_DeferredOperationJoinKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_DeferredOperationJoinKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_DeferredOperationJoinKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_DeferredOperationJoinKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_DeferredOperationJoinKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_DeferredOperationJoinKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_DeferredOperationJoinKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_DeferredOperationJoinKHR(VkDevice device, VkDeferredOperationKHR operation) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetCullMode(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetCullMode(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetCullMode(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetCullMode(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetCullMode(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetCullMode(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetCullMode(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetCullMode(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetCullModeEXT(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetCullModeEXT(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetCullModeEXT(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetCullModeEXT(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetCullModeEXT(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetCullModeEXT(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetCullModeEXT(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetCullModeEXT(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetFrontFace(VkCommandBuffer commandBuffer, VkFrontFace frontFace) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetFrontFace(VkCommandBuffer commandBuffer, VkFrontFace frontFace) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetFrontFace(VkCommandBuffer commandBuffer, VkFrontFace frontFace) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetFrontFace(VkCommandBuffer commandBuffer, VkFrontFace frontFace) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetFrontFace(VkCommandBuffer commandBuffer, VkFrontFace frontFace) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetFrontFace(VkCommandBuffer commandBuffer, VkFrontFace frontFace) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetFrontFace(VkCommandBuffer commandBuffer, VkFrontFace frontFace) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetFrontFace(VkCommandBuffer commandBuffer, VkFrontFace frontFace) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetFrontFaceEXT(VkCommandBuffer commandBuffer, VkFrontFace frontFace) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetFrontFaceEXT(VkCommandBuffer commandBuffer, VkFrontFace frontFace) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetFrontFaceEXT(VkCommandBuffer commandBuffer, VkFrontFace frontFace) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetFrontFaceEXT(VkCommandBuffer commandBuffer, VkFrontFace frontFace) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetFrontFaceEXT(VkCommandBuffer commandBuffer, VkFrontFace frontFace) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetFrontFaceEXT(VkCommandBuffer commandBuffer, VkFrontFace frontFace) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetFrontFaceEXT(VkCommandBuffer commandBuffer, VkFrontFace frontFace) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetFrontFaceEXT(VkCommandBuffer commandBuffer, VkFrontFace frontFace) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetPrimitiveTopology(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetPrimitiveTopology(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetPrimitiveTopology(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetPrimitiveTopology(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetPrimitiveTopology(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetPrimitiveTopology(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetPrimitiveTopology(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetPrimitiveTopology(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetPrimitiveTopologyEXT(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetPrimitiveTopologyEXT(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetPrimitiveTopologyEXT(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetPrimitiveTopologyEXT(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetPrimitiveTopologyEXT(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetPrimitiveTopologyEXT(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetPrimitiveTopologyEXT(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetPrimitiveTopologyEXT(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetViewportWithCount(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetViewportWithCount(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetViewportWithCount(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetViewportWithCount(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetViewportWithCount(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetViewportWithCount(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetViewportWithCount(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetViewportWithCount(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetViewportWithCountEXT(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetViewportWithCountEXT(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetViewportWithCountEXT(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetViewportWithCountEXT(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetViewportWithCountEXT(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetViewportWithCountEXT(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetViewportWithCountEXT(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetViewportWithCountEXT(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetScissorWithCount(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetScissorWithCount(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetScissorWithCount(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetScissorWithCount(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetScissorWithCount(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetScissorWithCount(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetScissorWithCount(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetScissorWithCount(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetScissorWithCountEXT(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetScissorWithCountEXT(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetScissorWithCountEXT(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetScissorWithCountEXT(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetScissorWithCountEXT(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetScissorWithCountEXT(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetScissorWithCountEXT(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetScissorWithCountEXT(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBindVertexBuffers2(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBindVertexBuffers2(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBindVertexBuffers2(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBindVertexBuffers2(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBindVertexBuffers2(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBindVertexBuffers2(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBindVertexBuffers2(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBindVertexBuffers2(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBindVertexBuffers2EXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBindVertexBuffers2EXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBindVertexBuffers2EXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBindVertexBuffers2EXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBindVertexBuffers2EXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBindVertexBuffers2EXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBindVertexBuffers2EXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBindVertexBuffers2EXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetDepthTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetDepthTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetDepthTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetDepthTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetDepthTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetDepthTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetDepthTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetDepthTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetDepthTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetDepthTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetDepthTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetDepthTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetDepthTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetDepthTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetDepthTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetDepthTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetDepthWriteEnable(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetDepthWriteEnable(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetDepthWriteEnable(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetDepthWriteEnable(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetDepthWriteEnable(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetDepthWriteEnable(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetDepthWriteEnable(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetDepthWriteEnable(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetDepthWriteEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetDepthWriteEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetDepthWriteEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetDepthWriteEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetDepthWriteEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetDepthWriteEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetDepthWriteEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetDepthWriteEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetDepthCompareOp(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetDepthCompareOp(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetDepthCompareOp(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetDepthCompareOp(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetDepthCompareOp(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetDepthCompareOp(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetDepthCompareOp(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetDepthCompareOp(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetDepthCompareOpEXT(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetDepthCompareOpEXT(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetDepthCompareOpEXT(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetDepthCompareOpEXT(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetDepthCompareOpEXT(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetDepthCompareOpEXT(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetDepthCompareOpEXT(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetDepthCompareOpEXT(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetDepthBoundsTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetDepthBoundsTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetDepthBoundsTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetDepthBoundsTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetDepthBoundsTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetDepthBoundsTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetDepthBoundsTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetDepthBoundsTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetDepthBoundsTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetDepthBoundsTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetDepthBoundsTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetDepthBoundsTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetDepthBoundsTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetDepthBoundsTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetDepthBoundsTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetDepthBoundsTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetStencilTestEnable(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetStencilTestEnable(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetStencilTestEnable(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetStencilTestEnable(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetStencilTestEnable(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetStencilTestEnable(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetStencilTestEnable(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetStencilTestEnable(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetStencilTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetStencilTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetStencilTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetStencilTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetStencilTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetStencilTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetStencilTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetStencilTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetStencilOp(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetStencilOp(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetStencilOp(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetStencilOp(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetStencilOp(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetStencilOp(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetStencilOp(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetStencilOp(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetStencilOpEXT(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetStencilOpEXT(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetStencilOpEXT(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetStencilOpEXT(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetStencilOpEXT(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetStencilOpEXT(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetStencilOpEXT(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetStencilOpEXT(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetPatchControlPointsEXT(VkCommandBuffer commandBuffer, uint32_t patchControlPoints) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetPatchControlPointsEXT(VkCommandBuffer commandBuffer, uint32_t patchControlPoints) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetPatchControlPointsEXT(VkCommandBuffer commandBuffer, uint32_t patchControlPoints) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetPatchControlPointsEXT(VkCommandBuffer commandBuffer, uint32_t patchControlPoints) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetPatchControlPointsEXT(VkCommandBuffer commandBuffer, uint32_t patchControlPoints) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetPatchControlPointsEXT(VkCommandBuffer commandBuffer, uint32_t patchControlPoints) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetPatchControlPointsEXT(VkCommandBuffer commandBuffer, uint32_t patchControlPoints) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetPatchControlPointsEXT(VkCommandBuffer commandBuffer, uint32_t patchControlPoints) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetRasterizerDiscardEnable(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetRasterizerDiscardEnable(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetRasterizerDiscardEnable(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetRasterizerDiscardEnable(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetRasterizerDiscardEnable(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetRasterizerDiscardEnable(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetRasterizerDiscardEnable(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetRasterizerDiscardEnable(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetRasterizerDiscardEnableEXT(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetRasterizerDiscardEnableEXT(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetRasterizerDiscardEnableEXT(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetRasterizerDiscardEnableEXT(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetRasterizerDiscardEnableEXT(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetRasterizerDiscardEnableEXT(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetRasterizerDiscardEnableEXT(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetRasterizerDiscardEnableEXT(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetDepthBiasEnable(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetDepthBiasEnable(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetDepthBiasEnable(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetDepthBiasEnable(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetDepthBiasEnable(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetDepthBiasEnable(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetDepthBiasEnable(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetDepthBiasEnable(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetDepthBiasEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetDepthBiasEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetDepthBiasEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetDepthBiasEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetDepthBiasEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetDepthBiasEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetDepthBiasEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetDepthBiasEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetLogicOpEXT(VkCommandBuffer commandBuffer, VkLogicOp logicOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetLogicOpEXT(VkCommandBuffer commandBuffer, VkLogicOp logicOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetLogicOpEXT(VkCommandBuffer commandBuffer, VkLogicOp logicOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetLogicOpEXT(VkCommandBuffer commandBuffer, VkLogicOp logicOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetLogicOpEXT(VkCommandBuffer commandBuffer, VkLogicOp logicOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetLogicOpEXT(VkCommandBuffer commandBuffer, VkLogicOp logicOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetLogicOpEXT(VkCommandBuffer commandBuffer, VkLogicOp logicOp) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetLogicOpEXT(VkCommandBuffer commandBuffer, VkLogicOp logicOp) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetPrimitiveRestartEnable(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetPrimitiveRestartEnable(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetPrimitiveRestartEnable(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetPrimitiveRestartEnable(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetPrimitiveRestartEnable(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetPrimitiveRestartEnable(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetPrimitiveRestartEnable(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetPrimitiveRestartEnable(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetPrimitiveRestartEnableEXT(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetPrimitiveRestartEnableEXT(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetPrimitiveRestartEnableEXT(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetPrimitiveRestartEnableEXT(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetPrimitiveRestartEnableEXT(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetPrimitiveRestartEnableEXT(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetPrimitiveRestartEnableEXT(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetPrimitiveRestartEnableEXT(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetTessellationDomainOriginEXT(VkCommandBuffer commandBuffer, VkTessellationDomainOrigin domainOrigin) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetTessellationDomainOriginEXT(VkCommandBuffer commandBuffer, VkTessellationDomainOrigin domainOrigin) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetTessellationDomainOriginEXT(VkCommandBuffer commandBuffer, VkTessellationDomainOrigin domainOrigin) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetTessellationDomainOriginEXT(VkCommandBuffer commandBuffer, VkTessellationDomainOrigin domainOrigin) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetTessellationDomainOriginEXT(VkCommandBuffer commandBuffer, VkTessellationDomainOrigin domainOrigin) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetTessellationDomainOriginEXT(VkCommandBuffer commandBuffer, VkTessellationDomainOrigin domainOrigin) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetTessellationDomainOriginEXT(VkCommandBuffer commandBuffer, VkTessellationDomainOrigin domainOrigin) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetTessellationDomainOriginEXT(VkCommandBuffer commandBuffer, VkTessellationDomainOrigin domainOrigin) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetDepthClampEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClampEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetDepthClampEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClampEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetDepthClampEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClampEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetDepthClampEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClampEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetDepthClampEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClampEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetDepthClampEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClampEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetDepthClampEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClampEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetDepthClampEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClampEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetPolygonModeEXT(VkCommandBuffer commandBuffer, VkPolygonMode polygonMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetPolygonModeEXT(VkCommandBuffer commandBuffer, VkPolygonMode polygonMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetPolygonModeEXT(VkCommandBuffer commandBuffer, VkPolygonMode polygonMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetPolygonModeEXT(VkCommandBuffer commandBuffer, VkPolygonMode polygonMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetPolygonModeEXT(VkCommandBuffer commandBuffer, VkPolygonMode polygonMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetPolygonModeEXT(VkCommandBuffer commandBuffer, VkPolygonMode polygonMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetPolygonModeEXT(VkCommandBuffer commandBuffer, VkPolygonMode polygonMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetPolygonModeEXT(VkCommandBuffer commandBuffer, VkPolygonMode polygonMode) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetRasterizationSamplesEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits  rasterizationSamples) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetRasterizationSamplesEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits  rasterizationSamples) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetRasterizationSamplesEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits  rasterizationSamples) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetRasterizationSamplesEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits  rasterizationSamples) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetRasterizationSamplesEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits  rasterizationSamples) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetRasterizationSamplesEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits  rasterizationSamples) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetRasterizationSamplesEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits  rasterizationSamples) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetRasterizationSamplesEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits  rasterizationSamples) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetSampleMaskEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits  samples, const VkSampleMask*    pSampleMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetSampleMaskEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits  samples, const VkSampleMask*    pSampleMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetSampleMaskEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits  samples, const VkSampleMask*    pSampleMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetSampleMaskEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits  samples, const VkSampleMask*    pSampleMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetSampleMaskEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits  samples, const VkSampleMask*    pSampleMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetSampleMaskEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits  samples, const VkSampleMask*    pSampleMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetSampleMaskEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits  samples, const VkSampleMask*    pSampleMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetSampleMaskEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits  samples, const VkSampleMask*    pSampleMask) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetAlphaToCoverageEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToCoverageEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetAlphaToCoverageEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToCoverageEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetAlphaToCoverageEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToCoverageEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetAlphaToCoverageEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToCoverageEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetAlphaToCoverageEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToCoverageEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetAlphaToCoverageEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToCoverageEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetAlphaToCoverageEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToCoverageEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetAlphaToCoverageEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToCoverageEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetAlphaToOneEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToOneEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetAlphaToOneEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToOneEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetAlphaToOneEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToOneEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetAlphaToOneEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToOneEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetAlphaToOneEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToOneEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetAlphaToOneEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToOneEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetAlphaToOneEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToOneEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetAlphaToOneEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToOneEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetLogicOpEnableEXT(VkCommandBuffer commandBuffer, VkBool32 logicOpEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetLogicOpEnableEXT(VkCommandBuffer commandBuffer, VkBool32 logicOpEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetLogicOpEnableEXT(VkCommandBuffer commandBuffer, VkBool32 logicOpEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetLogicOpEnableEXT(VkCommandBuffer commandBuffer, VkBool32 logicOpEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetLogicOpEnableEXT(VkCommandBuffer commandBuffer, VkBool32 logicOpEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetLogicOpEnableEXT(VkCommandBuffer commandBuffer, VkBool32 logicOpEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetLogicOpEnableEXT(VkCommandBuffer commandBuffer, VkBool32 logicOpEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetLogicOpEnableEXT(VkCommandBuffer commandBuffer, VkBool32 logicOpEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetColorBlendEnableEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkBool32* pColorBlendEnables) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetColorBlendEnableEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkBool32* pColorBlendEnables) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetColorBlendEnableEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkBool32* pColorBlendEnables) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetColorBlendEnableEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkBool32* pColorBlendEnables) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetColorBlendEnableEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkBool32* pColorBlendEnables) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetColorBlendEnableEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkBool32* pColorBlendEnables) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetColorBlendEnableEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkBool32* pColorBlendEnables) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetColorBlendEnableEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkBool32* pColorBlendEnables) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetColorBlendEquationEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendEquationEXT* pColorBlendEquations) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetColorBlendEquationEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendEquationEXT* pColorBlendEquations) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetColorBlendEquationEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendEquationEXT* pColorBlendEquations) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetColorBlendEquationEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendEquationEXT* pColorBlendEquations) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetColorBlendEquationEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendEquationEXT* pColorBlendEquations) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetColorBlendEquationEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendEquationEXT* pColorBlendEquations) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetColorBlendEquationEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendEquationEXT* pColorBlendEquations) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetColorBlendEquationEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendEquationEXT* pColorBlendEquations) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetColorWriteMaskEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorComponentFlags* pColorWriteMasks) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetColorWriteMaskEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorComponentFlags* pColorWriteMasks) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetColorWriteMaskEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorComponentFlags* pColorWriteMasks) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetColorWriteMaskEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorComponentFlags* pColorWriteMasks) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetColorWriteMaskEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorComponentFlags* pColorWriteMasks) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetColorWriteMaskEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorComponentFlags* pColorWriteMasks) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetColorWriteMaskEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorComponentFlags* pColorWriteMasks) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetColorWriteMaskEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorComponentFlags* pColorWriteMasks) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetRasterizationStreamEXT(VkCommandBuffer commandBuffer, uint32_t rasterizationStream) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetRasterizationStreamEXT(VkCommandBuffer commandBuffer, uint32_t rasterizationStream) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetRasterizationStreamEXT(VkCommandBuffer commandBuffer, uint32_t rasterizationStream) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetRasterizationStreamEXT(VkCommandBuffer commandBuffer, uint32_t rasterizationStream) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetRasterizationStreamEXT(VkCommandBuffer commandBuffer, uint32_t rasterizationStream) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetRasterizationStreamEXT(VkCommandBuffer commandBuffer, uint32_t rasterizationStream) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetRasterizationStreamEXT(VkCommandBuffer commandBuffer, uint32_t rasterizationStream) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetRasterizationStreamEXT(VkCommandBuffer commandBuffer, uint32_t rasterizationStream) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetConservativeRasterizationModeEXT(VkCommandBuffer commandBuffer, VkConservativeRasterizationModeEXT conservativeRasterizationMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetConservativeRasterizationModeEXT(VkCommandBuffer commandBuffer, VkConservativeRasterizationModeEXT conservativeRasterizationMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetConservativeRasterizationModeEXT(VkCommandBuffer commandBuffer, VkConservativeRasterizationModeEXT conservativeRasterizationMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetConservativeRasterizationModeEXT(VkCommandBuffer commandBuffer, VkConservativeRasterizationModeEXT conservativeRasterizationMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetConservativeRasterizationModeEXT(VkCommandBuffer commandBuffer, VkConservativeRasterizationModeEXT conservativeRasterizationMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetConservativeRasterizationModeEXT(VkCommandBuffer commandBuffer, VkConservativeRasterizationModeEXT conservativeRasterizationMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetConservativeRasterizationModeEXT(VkCommandBuffer commandBuffer, VkConservativeRasterizationModeEXT conservativeRasterizationMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetConservativeRasterizationModeEXT(VkCommandBuffer commandBuffer, VkConservativeRasterizationModeEXT conservativeRasterizationMode) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetExtraPrimitiveOverestimationSizeEXT(VkCommandBuffer commandBuffer, float extraPrimitiveOverestimationSize) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetExtraPrimitiveOverestimationSizeEXT(VkCommandBuffer commandBuffer, float extraPrimitiveOverestimationSize) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetExtraPrimitiveOverestimationSizeEXT(VkCommandBuffer commandBuffer, float extraPrimitiveOverestimationSize) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetExtraPrimitiveOverestimationSizeEXT(VkCommandBuffer commandBuffer, float extraPrimitiveOverestimationSize) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetExtraPrimitiveOverestimationSizeEXT(VkCommandBuffer commandBuffer, float extraPrimitiveOverestimationSize) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetExtraPrimitiveOverestimationSizeEXT(VkCommandBuffer commandBuffer, float extraPrimitiveOverestimationSize) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetExtraPrimitiveOverestimationSizeEXT(VkCommandBuffer commandBuffer, float extraPrimitiveOverestimationSize) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetExtraPrimitiveOverestimationSizeEXT(VkCommandBuffer commandBuffer, float extraPrimitiveOverestimationSize) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetDepthClipEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClipEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetDepthClipEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClipEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetDepthClipEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClipEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetDepthClipEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClipEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetDepthClipEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClipEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetDepthClipEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClipEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetDepthClipEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClipEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetDepthClipEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClipEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetSampleLocationsEnableEXT(VkCommandBuffer commandBuffer, VkBool32 sampleLocationsEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetSampleLocationsEnableEXT(VkCommandBuffer commandBuffer, VkBool32 sampleLocationsEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetSampleLocationsEnableEXT(VkCommandBuffer commandBuffer, VkBool32 sampleLocationsEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetSampleLocationsEnableEXT(VkCommandBuffer commandBuffer, VkBool32 sampleLocationsEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetSampleLocationsEnableEXT(VkCommandBuffer commandBuffer, VkBool32 sampleLocationsEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetSampleLocationsEnableEXT(VkCommandBuffer commandBuffer, VkBool32 sampleLocationsEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetSampleLocationsEnableEXT(VkCommandBuffer commandBuffer, VkBool32 sampleLocationsEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetSampleLocationsEnableEXT(VkCommandBuffer commandBuffer, VkBool32 sampleLocationsEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetColorBlendAdvancedEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendAdvancedEXT* pColorBlendAdvanced) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetColorBlendAdvancedEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendAdvancedEXT* pColorBlendAdvanced) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetColorBlendAdvancedEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendAdvancedEXT* pColorBlendAdvanced) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetColorBlendAdvancedEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendAdvancedEXT* pColorBlendAdvanced) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetColorBlendAdvancedEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendAdvancedEXT* pColorBlendAdvanced) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetColorBlendAdvancedEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendAdvancedEXT* pColorBlendAdvanced) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetColorBlendAdvancedEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendAdvancedEXT* pColorBlendAdvanced) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetColorBlendAdvancedEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendAdvancedEXT* pColorBlendAdvanced) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetProvokingVertexModeEXT(VkCommandBuffer commandBuffer, VkProvokingVertexModeEXT provokingVertexMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetProvokingVertexModeEXT(VkCommandBuffer commandBuffer, VkProvokingVertexModeEXT provokingVertexMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetProvokingVertexModeEXT(VkCommandBuffer commandBuffer, VkProvokingVertexModeEXT provokingVertexMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetProvokingVertexModeEXT(VkCommandBuffer commandBuffer, VkProvokingVertexModeEXT provokingVertexMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetProvokingVertexModeEXT(VkCommandBuffer commandBuffer, VkProvokingVertexModeEXT provokingVertexMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetProvokingVertexModeEXT(VkCommandBuffer commandBuffer, VkProvokingVertexModeEXT provokingVertexMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetProvokingVertexModeEXT(VkCommandBuffer commandBuffer, VkProvokingVertexModeEXT provokingVertexMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetProvokingVertexModeEXT(VkCommandBuffer commandBuffer, VkProvokingVertexModeEXT provokingVertexMode) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetLineRasterizationModeEXT(VkCommandBuffer commandBuffer, VkLineRasterizationModeEXT lineRasterizationMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetLineRasterizationModeEXT(VkCommandBuffer commandBuffer, VkLineRasterizationModeEXT lineRasterizationMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetLineRasterizationModeEXT(VkCommandBuffer commandBuffer, VkLineRasterizationModeEXT lineRasterizationMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetLineRasterizationModeEXT(VkCommandBuffer commandBuffer, VkLineRasterizationModeEXT lineRasterizationMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetLineRasterizationModeEXT(VkCommandBuffer commandBuffer, VkLineRasterizationModeEXT lineRasterizationMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetLineRasterizationModeEXT(VkCommandBuffer commandBuffer, VkLineRasterizationModeEXT lineRasterizationMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetLineRasterizationModeEXT(VkCommandBuffer commandBuffer, VkLineRasterizationModeEXT lineRasterizationMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetLineRasterizationModeEXT(VkCommandBuffer commandBuffer, VkLineRasterizationModeEXT lineRasterizationMode) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetLineStippleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stippledLineEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetLineStippleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stippledLineEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetLineStippleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stippledLineEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetLineStippleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stippledLineEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetLineStippleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stippledLineEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetLineStippleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stippledLineEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetLineStippleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stippledLineEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetLineStippleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stippledLineEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetDepthClipNegativeOneToOneEXT(VkCommandBuffer commandBuffer, VkBool32 negativeOneToOne) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetDepthClipNegativeOneToOneEXT(VkCommandBuffer commandBuffer, VkBool32 negativeOneToOne) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetDepthClipNegativeOneToOneEXT(VkCommandBuffer commandBuffer, VkBool32 negativeOneToOne) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetDepthClipNegativeOneToOneEXT(VkCommandBuffer commandBuffer, VkBool32 negativeOneToOne) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetDepthClipNegativeOneToOneEXT(VkCommandBuffer commandBuffer, VkBool32 negativeOneToOne) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetDepthClipNegativeOneToOneEXT(VkCommandBuffer commandBuffer, VkBool32 negativeOneToOne) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetDepthClipNegativeOneToOneEXT(VkCommandBuffer commandBuffer, VkBool32 negativeOneToOne) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetDepthClipNegativeOneToOneEXT(VkCommandBuffer commandBuffer, VkBool32 negativeOneToOne) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetViewportWScalingEnableNV(VkCommandBuffer commandBuffer, VkBool32 viewportWScalingEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetViewportWScalingEnableNV(VkCommandBuffer commandBuffer, VkBool32 viewportWScalingEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetViewportWScalingEnableNV(VkCommandBuffer commandBuffer, VkBool32 viewportWScalingEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetViewportWScalingEnableNV(VkCommandBuffer commandBuffer, VkBool32 viewportWScalingEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetViewportWScalingEnableNV(VkCommandBuffer commandBuffer, VkBool32 viewportWScalingEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetViewportWScalingEnableNV(VkCommandBuffer commandBuffer, VkBool32 viewportWScalingEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetViewportWScalingEnableNV(VkCommandBuffer commandBuffer, VkBool32 viewportWScalingEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetViewportWScalingEnableNV(VkCommandBuffer commandBuffer, VkBool32 viewportWScalingEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetViewportSwizzleNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportSwizzleNV* pViewportSwizzles) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetViewportSwizzleNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportSwizzleNV* pViewportSwizzles) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetViewportSwizzleNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportSwizzleNV* pViewportSwizzles) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetViewportSwizzleNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportSwizzleNV* pViewportSwizzles) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetViewportSwizzleNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportSwizzleNV* pViewportSwizzles) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetViewportSwizzleNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportSwizzleNV* pViewportSwizzles) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetViewportSwizzleNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportSwizzleNV* pViewportSwizzles) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetViewportSwizzleNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportSwizzleNV* pViewportSwizzles) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetCoverageToColorEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageToColorEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetCoverageToColorEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageToColorEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetCoverageToColorEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageToColorEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetCoverageToColorEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageToColorEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetCoverageToColorEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageToColorEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetCoverageToColorEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageToColorEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetCoverageToColorEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageToColorEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetCoverageToColorEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageToColorEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetCoverageToColorLocationNV(VkCommandBuffer commandBuffer, uint32_t coverageToColorLocation) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetCoverageToColorLocationNV(VkCommandBuffer commandBuffer, uint32_t coverageToColorLocation) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetCoverageToColorLocationNV(VkCommandBuffer commandBuffer, uint32_t coverageToColorLocation) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetCoverageToColorLocationNV(VkCommandBuffer commandBuffer, uint32_t coverageToColorLocation) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetCoverageToColorLocationNV(VkCommandBuffer commandBuffer, uint32_t coverageToColorLocation) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetCoverageToColorLocationNV(VkCommandBuffer commandBuffer, uint32_t coverageToColorLocation) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetCoverageToColorLocationNV(VkCommandBuffer commandBuffer, uint32_t coverageToColorLocation) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetCoverageToColorLocationNV(VkCommandBuffer commandBuffer, uint32_t coverageToColorLocation) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetCoverageModulationModeNV(VkCommandBuffer commandBuffer, VkCoverageModulationModeNV coverageModulationMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetCoverageModulationModeNV(VkCommandBuffer commandBuffer, VkCoverageModulationModeNV coverageModulationMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetCoverageModulationModeNV(VkCommandBuffer commandBuffer, VkCoverageModulationModeNV coverageModulationMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetCoverageModulationModeNV(VkCommandBuffer commandBuffer, VkCoverageModulationModeNV coverageModulationMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetCoverageModulationModeNV(VkCommandBuffer commandBuffer, VkCoverageModulationModeNV coverageModulationMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetCoverageModulationModeNV(VkCommandBuffer commandBuffer, VkCoverageModulationModeNV coverageModulationMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetCoverageModulationModeNV(VkCommandBuffer commandBuffer, VkCoverageModulationModeNV coverageModulationMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetCoverageModulationModeNV(VkCommandBuffer commandBuffer, VkCoverageModulationModeNV coverageModulationMode) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetCoverageModulationTableEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageModulationTableEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetCoverageModulationTableEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageModulationTableEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetCoverageModulationTableEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageModulationTableEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetCoverageModulationTableEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageModulationTableEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetCoverageModulationTableEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageModulationTableEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetCoverageModulationTableEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageModulationTableEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetCoverageModulationTableEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageModulationTableEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetCoverageModulationTableEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageModulationTableEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetCoverageModulationTableNV(VkCommandBuffer commandBuffer, uint32_t coverageModulationTableCount, const float* pCoverageModulationTable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetCoverageModulationTableNV(VkCommandBuffer commandBuffer, uint32_t coverageModulationTableCount, const float* pCoverageModulationTable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetCoverageModulationTableNV(VkCommandBuffer commandBuffer, uint32_t coverageModulationTableCount, const float* pCoverageModulationTable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetCoverageModulationTableNV(VkCommandBuffer commandBuffer, uint32_t coverageModulationTableCount, const float* pCoverageModulationTable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetCoverageModulationTableNV(VkCommandBuffer commandBuffer, uint32_t coverageModulationTableCount, const float* pCoverageModulationTable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetCoverageModulationTableNV(VkCommandBuffer commandBuffer, uint32_t coverageModulationTableCount, const float* pCoverageModulationTable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetCoverageModulationTableNV(VkCommandBuffer commandBuffer, uint32_t coverageModulationTableCount, const float* pCoverageModulationTable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetCoverageModulationTableNV(VkCommandBuffer commandBuffer, uint32_t coverageModulationTableCount, const float* pCoverageModulationTable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetShadingRateImageEnableNV(VkCommandBuffer commandBuffer, VkBool32 shadingRateImageEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetShadingRateImageEnableNV(VkCommandBuffer commandBuffer, VkBool32 shadingRateImageEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetShadingRateImageEnableNV(VkCommandBuffer commandBuffer, VkBool32 shadingRateImageEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetShadingRateImageEnableNV(VkCommandBuffer commandBuffer, VkBool32 shadingRateImageEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetShadingRateImageEnableNV(VkCommandBuffer commandBuffer, VkBool32 shadingRateImageEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetShadingRateImageEnableNV(VkCommandBuffer commandBuffer, VkBool32 shadingRateImageEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetShadingRateImageEnableNV(VkCommandBuffer commandBuffer, VkBool32 shadingRateImageEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetShadingRateImageEnableNV(VkCommandBuffer commandBuffer, VkBool32 shadingRateImageEnable) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetCoverageReductionModeNV(VkCommandBuffer commandBuffer, VkCoverageReductionModeNV coverageReductionMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetCoverageReductionModeNV(VkCommandBuffer commandBuffer, VkCoverageReductionModeNV coverageReductionMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetCoverageReductionModeNV(VkCommandBuffer commandBuffer, VkCoverageReductionModeNV coverageReductionMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetCoverageReductionModeNV(VkCommandBuffer commandBuffer, VkCoverageReductionModeNV coverageReductionMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetCoverageReductionModeNV(VkCommandBuffer commandBuffer, VkCoverageReductionModeNV coverageReductionMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetCoverageReductionModeNV(VkCommandBuffer commandBuffer, VkCoverageReductionModeNV coverageReductionMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetCoverageReductionModeNV(VkCommandBuffer commandBuffer, VkCoverageReductionModeNV coverageReductionMode) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetCoverageReductionModeNV(VkCommandBuffer commandBuffer, VkCoverageReductionModeNV coverageReductionMode) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetRepresentativeFragmentTestEnableNV(VkCommandBuffer commandBuffer, VkBool32 representativeFragmentTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetRepresentativeFragmentTestEnableNV(VkCommandBuffer commandBuffer, VkBool32 representativeFragmentTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetRepresentativeFragmentTestEnableNV(VkCommandBuffer commandBuffer, VkBool32 representativeFragmentTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetRepresentativeFragmentTestEnableNV(VkCommandBuffer commandBuffer, VkBool32 representativeFragmentTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetRepresentativeFragmentTestEnableNV(VkCommandBuffer commandBuffer, VkBool32 representativeFragmentTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetRepresentativeFragmentTestEnableNV(VkCommandBuffer commandBuffer, VkBool32 representativeFragmentTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetRepresentativeFragmentTestEnableNV(VkCommandBuffer commandBuffer, VkBool32 representativeFragmentTestEnable) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetRepresentativeFragmentTestEnableNV(VkCommandBuffer commandBuffer, VkBool32 representativeFragmentTestEnable) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreatePrivateDataSlot(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreatePrivateDataSlot(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreatePrivateDataSlot(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreatePrivateDataSlot(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreatePrivateDataSlot(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreatePrivateDataSlot(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreatePrivateDataSlot(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreatePrivateDataSlot(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreatePrivateDataSlotEXT(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreatePrivateDataSlotEXT(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreatePrivateDataSlotEXT(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreatePrivateDataSlotEXT(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreatePrivateDataSlotEXT(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreatePrivateDataSlotEXT(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreatePrivateDataSlotEXT(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreatePrivateDataSlotEXT(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyPrivateDataSlot(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyPrivateDataSlot(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyPrivateDataSlot(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyPrivateDataSlot(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyPrivateDataSlot(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyPrivateDataSlot(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyPrivateDataSlot(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyPrivateDataSlot(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyPrivateDataSlotEXT(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyPrivateDataSlotEXT(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyPrivateDataSlotEXT(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyPrivateDataSlotEXT(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyPrivateDataSlotEXT(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyPrivateDataSlotEXT(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyPrivateDataSlotEXT(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyPrivateDataSlotEXT(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_SetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_SetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_SetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_SetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_SetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_SetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_SetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_SetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_SetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_SetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_SetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_SetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_SetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_SetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_SetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_SetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCopyBuffer2(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCopyBuffer2(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCopyBuffer2(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCopyBuffer2(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCopyBuffer2(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCopyBuffer2(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCopyBuffer2(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCopyBuffer2(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCopyBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCopyBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCopyBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCopyBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCopyBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCopyBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCopyBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCopyBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCopyImage2(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCopyImage2(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCopyImage2(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCopyImage2(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCopyImage2(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCopyImage2(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCopyImage2(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCopyImage2(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCopyImage2KHR(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCopyImage2KHR(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCopyImage2KHR(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCopyImage2KHR(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCopyImage2KHR(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCopyImage2KHR(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCopyImage2KHR(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCopyImage2KHR(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBlitImage2(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBlitImage2(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBlitImage2(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBlitImage2(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBlitImage2(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBlitImage2(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBlitImage2(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBlitImage2(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBlitImage2KHR(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBlitImage2KHR(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBlitImage2KHR(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBlitImage2KHR(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBlitImage2KHR(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBlitImage2KHR(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBlitImage2KHR(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBlitImage2KHR(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCopyBufferToImage2(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCopyBufferToImage2(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCopyBufferToImage2(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCopyBufferToImage2(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCopyBufferToImage2(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCopyBufferToImage2(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCopyBufferToImage2(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCopyBufferToImage2(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCopyBufferToImage2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCopyBufferToImage2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCopyBufferToImage2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCopyBufferToImage2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCopyBufferToImage2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCopyBufferToImage2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCopyBufferToImage2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCopyBufferToImage2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCopyImageToBuffer2(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCopyImageToBuffer2(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCopyImageToBuffer2(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCopyImageToBuffer2(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCopyImageToBuffer2(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCopyImageToBuffer2(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCopyImageToBuffer2(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCopyImageToBuffer2(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCopyImageToBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCopyImageToBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCopyImageToBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCopyImageToBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCopyImageToBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCopyImageToBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCopyImageToBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCopyImageToBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdResolveImage2(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdResolveImage2(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdResolveImage2(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdResolveImage2(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdResolveImage2(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdResolveImage2(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdResolveImage2(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdResolveImage2(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdResolveImage2KHR(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdResolveImage2KHR(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdResolveImage2KHR(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdResolveImage2KHR(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdResolveImage2KHR(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdResolveImage2KHR(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdResolveImage2KHR(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdResolveImage2KHR(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetFragmentShadingRateKHR(VkCommandBuffer           commandBuffer, const VkExtent2D*                           pFragmentSize, const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetFragmentShadingRateKHR(VkCommandBuffer           commandBuffer, const VkExtent2D*                           pFragmentSize, const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetFragmentShadingRateKHR(VkCommandBuffer           commandBuffer, const VkExtent2D*                           pFragmentSize, const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetFragmentShadingRateKHR(VkCommandBuffer           commandBuffer, const VkExtent2D*                           pFragmentSize, const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetFragmentShadingRateKHR(VkCommandBuffer           commandBuffer, const VkExtent2D*                           pFragmentSize, const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetFragmentShadingRateKHR(VkCommandBuffer           commandBuffer, const VkExtent2D*                           pFragmentSize, const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetFragmentShadingRateKHR(VkCommandBuffer           commandBuffer, const VkExtent2D*                           pFragmentSize, const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetFragmentShadingRateKHR(VkCommandBuffer           commandBuffer, const VkExtent2D*                           pFragmentSize, const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetFragmentShadingRateEnumNV(VkCommandBuffer           commandBuffer, VkFragmentShadingRateNV                     shadingRate, const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetFragmentShadingRateEnumNV(VkCommandBuffer           commandBuffer, VkFragmentShadingRateNV                     shadingRate, const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetFragmentShadingRateEnumNV(VkCommandBuffer           commandBuffer, VkFragmentShadingRateNV                     shadingRate, const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetFragmentShadingRateEnumNV(VkCommandBuffer           commandBuffer, VkFragmentShadingRateNV                     shadingRate, const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetFragmentShadingRateEnumNV(VkCommandBuffer           commandBuffer, VkFragmentShadingRateNV                     shadingRate, const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetFragmentShadingRateEnumNV(VkCommandBuffer           commandBuffer, VkFragmentShadingRateNV                     shadingRate, const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetFragmentShadingRateEnumNV(VkCommandBuffer           commandBuffer, VkFragmentShadingRateNV                     shadingRate, const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetFragmentShadingRateEnumNV(VkCommandBuffer           commandBuffer, VkFragmentShadingRateNV                     shadingRate, const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetAccelerationStructureBuildSizesKHR(VkDevice                                            device, VkAccelerationStructureBuildTypeKHR                 buildType, const VkAccelerationStructureBuildGeometryInfoKHR*  pBuildInfo, const uint32_t*  pMaxPrimitiveCounts, VkAccelerationStructureBuildSizesInfoKHR*           pSizeInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetAccelerationStructureBuildSizesKHR(VkDevice                                            device, VkAccelerationStructureBuildTypeKHR                 buildType, const VkAccelerationStructureBuildGeometryInfoKHR*  pBuildInfo, const uint32_t*  pMaxPrimitiveCounts, VkAccelerationStructureBuildSizesInfoKHR*           pSizeInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetAccelerationStructureBuildSizesKHR(VkDevice                                            device, VkAccelerationStructureBuildTypeKHR                 buildType, const VkAccelerationStructureBuildGeometryInfoKHR*  pBuildInfo, const uint32_t*  pMaxPrimitiveCounts, VkAccelerationStructureBuildSizesInfoKHR*           pSizeInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetAccelerationStructureBuildSizesKHR(VkDevice                                            device, VkAccelerationStructureBuildTypeKHR                 buildType, const VkAccelerationStructureBuildGeometryInfoKHR*  pBuildInfo, const uint32_t*  pMaxPrimitiveCounts, VkAccelerationStructureBuildSizesInfoKHR*           pSizeInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetAccelerationStructureBuildSizesKHR(VkDevice                                            device, VkAccelerationStructureBuildTypeKHR                 buildType, const VkAccelerationStructureBuildGeometryInfoKHR*  pBuildInfo, const uint32_t*  pMaxPrimitiveCounts, VkAccelerationStructureBuildSizesInfoKHR*           pSizeInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetAccelerationStructureBuildSizesKHR(VkDevice                                            device, VkAccelerationStructureBuildTypeKHR                 buildType, const VkAccelerationStructureBuildGeometryInfoKHR*  pBuildInfo, const uint32_t*  pMaxPrimitiveCounts, VkAccelerationStructureBuildSizesInfoKHR*           pSizeInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetAccelerationStructureBuildSizesKHR(VkDevice                                            device, VkAccelerationStructureBuildTypeKHR                 buildType, const VkAccelerationStructureBuildGeometryInfoKHR*  pBuildInfo, const uint32_t*  pMaxPrimitiveCounts, VkAccelerationStructureBuildSizesInfoKHR*           pSizeInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetAccelerationStructureBuildSizesKHR(VkDevice                                            device, VkAccelerationStructureBuildTypeKHR                 buildType, const VkAccelerationStructureBuildGeometryInfoKHR*  pBuildInfo, const uint32_t*  pMaxPrimitiveCounts, VkAccelerationStructureBuildSizesInfoKHR*           pSizeInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetVertexInputEXT(VkCommandBuffer commandBuffer, uint32_t vertexBindingDescriptionCount, const VkVertexInputBindingDescription2EXT* pVertexBindingDescriptions, uint32_t vertexAttributeDescriptionCount, const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetVertexInputEXT(VkCommandBuffer commandBuffer, uint32_t vertexBindingDescriptionCount, const VkVertexInputBindingDescription2EXT* pVertexBindingDescriptions, uint32_t vertexAttributeDescriptionCount, const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetVertexInputEXT(VkCommandBuffer commandBuffer, uint32_t vertexBindingDescriptionCount, const VkVertexInputBindingDescription2EXT* pVertexBindingDescriptions, uint32_t vertexAttributeDescriptionCount, const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetVertexInputEXT(VkCommandBuffer commandBuffer, uint32_t vertexBindingDescriptionCount, const VkVertexInputBindingDescription2EXT* pVertexBindingDescriptions, uint32_t vertexAttributeDescriptionCount, const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetVertexInputEXT(VkCommandBuffer commandBuffer, uint32_t vertexBindingDescriptionCount, const VkVertexInputBindingDescription2EXT* pVertexBindingDescriptions, uint32_t vertexAttributeDescriptionCount, const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetVertexInputEXT(VkCommandBuffer commandBuffer, uint32_t vertexBindingDescriptionCount, const VkVertexInputBindingDescription2EXT* pVertexBindingDescriptions, uint32_t vertexAttributeDescriptionCount, const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetVertexInputEXT(VkCommandBuffer commandBuffer, uint32_t vertexBindingDescriptionCount, const VkVertexInputBindingDescription2EXT* pVertexBindingDescriptions, uint32_t vertexAttributeDescriptionCount, const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetVertexInputEXT(VkCommandBuffer commandBuffer, uint32_t vertexBindingDescriptionCount, const VkVertexInputBindingDescription2EXT* pVertexBindingDescriptions, uint32_t vertexAttributeDescriptionCount, const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetColorWriteEnableEXT(VkCommandBuffer       commandBuffer, uint32_t                                attachmentCount, const VkBool32*   pColorWriteEnables) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetColorWriteEnableEXT(VkCommandBuffer       commandBuffer, uint32_t                                attachmentCount, const VkBool32*   pColorWriteEnables) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetColorWriteEnableEXT(VkCommandBuffer       commandBuffer, uint32_t                                attachmentCount, const VkBool32*   pColorWriteEnables) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetColorWriteEnableEXT(VkCommandBuffer       commandBuffer, uint32_t                                attachmentCount, const VkBool32*   pColorWriteEnables) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetColorWriteEnableEXT(VkCommandBuffer       commandBuffer, uint32_t                                attachmentCount, const VkBool32*   pColorWriteEnables) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetColorWriteEnableEXT(VkCommandBuffer       commandBuffer, uint32_t                                attachmentCount, const VkBool32*   pColorWriteEnables) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetColorWriteEnableEXT(VkCommandBuffer       commandBuffer, uint32_t                                attachmentCount, const VkBool32*   pColorWriteEnables) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetColorWriteEnableEXT(VkCommandBuffer       commandBuffer, uint32_t                                attachmentCount, const VkBool32*   pColorWriteEnables) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetEvent2(VkCommandBuffer                   commandBuffer, VkEvent                                             event, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetEvent2(VkCommandBuffer                   commandBuffer, VkEvent                                             event, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetEvent2(VkCommandBuffer                   commandBuffer, VkEvent                                             event, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetEvent2(VkCommandBuffer                   commandBuffer, VkEvent                                             event, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetEvent2(VkCommandBuffer                   commandBuffer, VkEvent                                             event, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetEvent2(VkCommandBuffer                   commandBuffer, VkEvent                                             event, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetEvent2(VkCommandBuffer                   commandBuffer, VkEvent                                             event, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetEvent2(VkCommandBuffer                   commandBuffer, VkEvent                                             event, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetEvent2KHR(VkCommandBuffer                   commandBuffer, VkEvent                                             event, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetEvent2KHR(VkCommandBuffer                   commandBuffer, VkEvent                                             event, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetEvent2KHR(VkCommandBuffer                   commandBuffer, VkEvent                                             event, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetEvent2KHR(VkCommandBuffer                   commandBuffer, VkEvent                                             event, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetEvent2KHR(VkCommandBuffer                   commandBuffer, VkEvent                                             event, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetEvent2KHR(VkCommandBuffer                   commandBuffer, VkEvent                                             event, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetEvent2KHR(VkCommandBuffer                   commandBuffer, VkEvent                                             event, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetEvent2KHR(VkCommandBuffer                   commandBuffer, VkEvent                                             event, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdResetEvent2(VkCommandBuffer                   commandBuffer, VkEvent                                             event, VkPipelineStageFlags2               stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdResetEvent2(VkCommandBuffer                   commandBuffer, VkEvent                                             event, VkPipelineStageFlags2               stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdResetEvent2(VkCommandBuffer                   commandBuffer, VkEvent                                             event, VkPipelineStageFlags2               stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdResetEvent2(VkCommandBuffer                   commandBuffer, VkEvent                                             event, VkPipelineStageFlags2               stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdResetEvent2(VkCommandBuffer                   commandBuffer, VkEvent                                             event, VkPipelineStageFlags2               stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdResetEvent2(VkCommandBuffer                   commandBuffer, VkEvent                                             event, VkPipelineStageFlags2               stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdResetEvent2(VkCommandBuffer                   commandBuffer, VkEvent                                             event, VkPipelineStageFlags2               stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdResetEvent2(VkCommandBuffer                   commandBuffer, VkEvent                                             event, VkPipelineStageFlags2               stageMask) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdResetEvent2KHR(VkCommandBuffer                   commandBuffer, VkEvent                                             event, VkPipelineStageFlags2               stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdResetEvent2KHR(VkCommandBuffer                   commandBuffer, VkEvent                                             event, VkPipelineStageFlags2               stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdResetEvent2KHR(VkCommandBuffer                   commandBuffer, VkEvent                                             event, VkPipelineStageFlags2               stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdResetEvent2KHR(VkCommandBuffer                   commandBuffer, VkEvent                                             event, VkPipelineStageFlags2               stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdResetEvent2KHR(VkCommandBuffer                   commandBuffer, VkEvent                                             event, VkPipelineStageFlags2               stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdResetEvent2KHR(VkCommandBuffer                   commandBuffer, VkEvent                                             event, VkPipelineStageFlags2               stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdResetEvent2KHR(VkCommandBuffer                   commandBuffer, VkEvent                                             event, VkPipelineStageFlags2               stageMask) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdResetEvent2KHR(VkCommandBuffer                   commandBuffer, VkEvent                                             event, VkPipelineStageFlags2               stageMask) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdWaitEvents2(VkCommandBuffer                   commandBuffer, uint32_t                                            eventCount, const VkEvent*                     pEvents, const VkDependencyInfo*            pDependencyInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdWaitEvents2(VkCommandBuffer                   commandBuffer, uint32_t                                            eventCount, const VkEvent*                     pEvents, const VkDependencyInfo*            pDependencyInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdWaitEvents2(VkCommandBuffer                   commandBuffer, uint32_t                                            eventCount, const VkEvent*                     pEvents, const VkDependencyInfo*            pDependencyInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdWaitEvents2(VkCommandBuffer                   commandBuffer, uint32_t                                            eventCount, const VkEvent*                     pEvents, const VkDependencyInfo*            pDependencyInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdWaitEvents2(VkCommandBuffer                   commandBuffer, uint32_t                                            eventCount, const VkEvent*                     pEvents, const VkDependencyInfo*            pDependencyInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdWaitEvents2(VkCommandBuffer                   commandBuffer, uint32_t                                            eventCount, const VkEvent*                     pEvents, const VkDependencyInfo*            pDependencyInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdWaitEvents2(VkCommandBuffer                   commandBuffer, uint32_t                                            eventCount, const VkEvent*                     pEvents, const VkDependencyInfo*            pDependencyInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdWaitEvents2(VkCommandBuffer                   commandBuffer, uint32_t                                            eventCount, const VkEvent*                     pEvents, const VkDependencyInfo*            pDependencyInfos) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdWaitEvents2KHR(VkCommandBuffer                   commandBuffer, uint32_t                                            eventCount, const VkEvent*                     pEvents, const VkDependencyInfo*            pDependencyInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdWaitEvents2KHR(VkCommandBuffer                   commandBuffer, uint32_t                                            eventCount, const VkEvent*                     pEvents, const VkDependencyInfo*            pDependencyInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdWaitEvents2KHR(VkCommandBuffer                   commandBuffer, uint32_t                                            eventCount, const VkEvent*                     pEvents, const VkDependencyInfo*            pDependencyInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdWaitEvents2KHR(VkCommandBuffer                   commandBuffer, uint32_t                                            eventCount, const VkEvent*                     pEvents, const VkDependencyInfo*            pDependencyInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdWaitEvents2KHR(VkCommandBuffer                   commandBuffer, uint32_t                                            eventCount, const VkEvent*                     pEvents, const VkDependencyInfo*            pDependencyInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdWaitEvents2KHR(VkCommandBuffer                   commandBuffer, uint32_t                                            eventCount, const VkEvent*                     pEvents, const VkDependencyInfo*            pDependencyInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdWaitEvents2KHR(VkCommandBuffer                   commandBuffer, uint32_t                                            eventCount, const VkEvent*                     pEvents, const VkDependencyInfo*            pDependencyInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdWaitEvents2KHR(VkCommandBuffer                   commandBuffer, uint32_t                                            eventCount, const VkEvent*                     pEvents, const VkDependencyInfo*            pDependencyInfos) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdPipelineBarrier2(VkCommandBuffer                   commandBuffer, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdPipelineBarrier2(VkCommandBuffer                   commandBuffer, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdPipelineBarrier2(VkCommandBuffer                   commandBuffer, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdPipelineBarrier2(VkCommandBuffer                   commandBuffer, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdPipelineBarrier2(VkCommandBuffer                   commandBuffer, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdPipelineBarrier2(VkCommandBuffer                   commandBuffer, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdPipelineBarrier2(VkCommandBuffer                   commandBuffer, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdPipelineBarrier2(VkCommandBuffer                   commandBuffer, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdPipelineBarrier2KHR(VkCommandBuffer                   commandBuffer, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdPipelineBarrier2KHR(VkCommandBuffer                   commandBuffer, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdPipelineBarrier2KHR(VkCommandBuffer                   commandBuffer, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdPipelineBarrier2KHR(VkCommandBuffer                   commandBuffer, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdPipelineBarrier2KHR(VkCommandBuffer                   commandBuffer, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdPipelineBarrier2KHR(VkCommandBuffer                   commandBuffer, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdPipelineBarrier2KHR(VkCommandBuffer                   commandBuffer, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdPipelineBarrier2KHR(VkCommandBuffer                   commandBuffer, const VkDependencyInfo*                             pDependencyInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_QueueSubmit2(VkQueue                           queue, uint32_t                            submitCount, const VkSubmitInfo2*              pSubmits, VkFence           fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_QueueSubmit2(VkQueue                           queue, uint32_t                            submitCount, const VkSubmitInfo2*              pSubmits, VkFence           fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_QueueSubmit2(VkQueue                           queue, uint32_t                            submitCount, const VkSubmitInfo2*              pSubmits, VkFence           fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_QueueSubmit2(VkQueue                           queue, uint32_t                            submitCount, const VkSubmitInfo2*              pSubmits, VkFence           fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_QueueSubmit2(VkQueue                           queue, uint32_t                            submitCount, const VkSubmitInfo2*              pSubmits, VkFence           fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_QueueSubmit2(VkQueue                           queue, uint32_t                            submitCount, const VkSubmitInfo2*              pSubmits, VkFence           fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_QueueSubmit2(VkQueue                           queue, uint32_t                            submitCount, const VkSubmitInfo2*              pSubmits, VkFence           fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_QueueSubmit2(VkQueue                           queue, uint32_t                            submitCount, const VkSubmitInfo2*              pSubmits, VkFence           fence) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_QueueSubmit2KHR(VkQueue                           queue, uint32_t                            submitCount, const VkSubmitInfo2*              pSubmits, VkFence           fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_QueueSubmit2KHR(VkQueue                           queue, uint32_t                            submitCount, const VkSubmitInfo2*              pSubmits, VkFence           fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_QueueSubmit2KHR(VkQueue                           queue, uint32_t                            submitCount, const VkSubmitInfo2*              pSubmits, VkFence           fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_QueueSubmit2KHR(VkQueue                           queue, uint32_t                            submitCount, const VkSubmitInfo2*              pSubmits, VkFence           fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_QueueSubmit2KHR(VkQueue                           queue, uint32_t                            submitCount, const VkSubmitInfo2*              pSubmits, VkFence           fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_QueueSubmit2KHR(VkQueue                           queue, uint32_t                            submitCount, const VkSubmitInfo2*              pSubmits, VkFence           fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_QueueSubmit2KHR(VkQueue                           queue, uint32_t                            submitCount, const VkSubmitInfo2*              pSubmits, VkFence           fence) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_QueueSubmit2KHR(VkQueue                           queue, uint32_t                            submitCount, const VkSubmitInfo2*              pSubmits, VkFence           fence) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdWriteTimestamp2(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkQueryPool                                         queryPool, uint32_t                                            query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdWriteTimestamp2(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkQueryPool                                         queryPool, uint32_t                                            query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdWriteTimestamp2(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkQueryPool                                         queryPool, uint32_t                                            query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdWriteTimestamp2(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkQueryPool                                         queryPool, uint32_t                                            query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdWriteTimestamp2(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkQueryPool                                         queryPool, uint32_t                                            query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdWriteTimestamp2(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkQueryPool                                         queryPool, uint32_t                                            query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdWriteTimestamp2(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkQueryPool                                         queryPool, uint32_t                                            query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdWriteTimestamp2(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkQueryPool                                         queryPool, uint32_t                                            query) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdWriteTimestamp2KHR(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkQueryPool                                         queryPool, uint32_t                                            query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdWriteTimestamp2KHR(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkQueryPool                                         queryPool, uint32_t                                            query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdWriteTimestamp2KHR(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkQueryPool                                         queryPool, uint32_t                                            query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdWriteTimestamp2KHR(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkQueryPool                                         queryPool, uint32_t                                            query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdWriteTimestamp2KHR(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkQueryPool                                         queryPool, uint32_t                                            query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdWriteTimestamp2KHR(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkQueryPool                                         queryPool, uint32_t                                            query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdWriteTimestamp2KHR(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkQueryPool                                         queryPool, uint32_t                                            query) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdWriteTimestamp2KHR(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkQueryPool                                         queryPool, uint32_t                                            query) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdWriteBufferMarker2AMD(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkBuffer                                            dstBuffer, VkDeviceSize                                        dstOffset, uint32_t                                            marker) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdWriteBufferMarker2AMD(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkBuffer                                            dstBuffer, VkDeviceSize                                        dstOffset, uint32_t                                            marker) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdWriteBufferMarker2AMD(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkBuffer                                            dstBuffer, VkDeviceSize                                        dstOffset, uint32_t                                            marker) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdWriteBufferMarker2AMD(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkBuffer                                            dstBuffer, VkDeviceSize                                        dstOffset, uint32_t                                            marker) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdWriteBufferMarker2AMD(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkBuffer                                            dstBuffer, VkDeviceSize                                        dstOffset, uint32_t                                            marker) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdWriteBufferMarker2AMD(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkBuffer                                            dstBuffer, VkDeviceSize                                        dstOffset, uint32_t                                            marker) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdWriteBufferMarker2AMD(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkBuffer                                            dstBuffer, VkDeviceSize                                        dstOffset, uint32_t                                            marker) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdWriteBufferMarker2AMD(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkBuffer                                            dstBuffer, VkDeviceSize                                        dstOffset, uint32_t                                            marker) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetQueueCheckpointData2NV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointData2NV* pCheckpointData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetQueueCheckpointData2NV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointData2NV* pCheckpointData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetQueueCheckpointData2NV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointData2NV* pCheckpointData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetQueueCheckpointData2NV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointData2NV* pCheckpointData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetQueueCheckpointData2NV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointData2NV* pCheckpointData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetQueueCheckpointData2NV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointData2NV* pCheckpointData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetQueueCheckpointData2NV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointData2NV* pCheckpointData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetQueueCheckpointData2NV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointData2NV* pCheckpointData) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateVideoSessionKHR(VkDevice device, const VkVideoSessionCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionKHR* pVideoSession) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateVideoSessionKHR(VkDevice device, const VkVideoSessionCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionKHR* pVideoSession) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateVideoSessionKHR(VkDevice device, const VkVideoSessionCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionKHR* pVideoSession) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateVideoSessionKHR(VkDevice device, const VkVideoSessionCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionKHR* pVideoSession) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateVideoSessionKHR(VkDevice device, const VkVideoSessionCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionKHR* pVideoSession) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateVideoSessionKHR(VkDevice device, const VkVideoSessionCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionKHR* pVideoSession) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateVideoSessionKHR(VkDevice device, const VkVideoSessionCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionKHR* pVideoSession) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateVideoSessionKHR(VkDevice device, const VkVideoSessionCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionKHR* pVideoSession) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyVideoSessionKHR(VkDevice device, VkVideoSessionKHR videoSession, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyVideoSessionKHR(VkDevice device, VkVideoSessionKHR videoSession, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyVideoSessionKHR(VkDevice device, VkVideoSessionKHR videoSession, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyVideoSessionKHR(VkDevice device, VkVideoSessionKHR videoSession, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyVideoSessionKHR(VkDevice device, VkVideoSessionKHR videoSession, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyVideoSessionKHR(VkDevice device, VkVideoSessionKHR videoSession, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyVideoSessionKHR(VkDevice device, VkVideoSessionKHR videoSession, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyVideoSessionKHR(VkDevice device, VkVideoSessionKHR videoSession, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateVideoSessionParametersKHR(VkDevice device, const VkVideoSessionParametersCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionParametersKHR* pVideoSessionParameters) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateVideoSessionParametersKHR(VkDevice device, const VkVideoSessionParametersCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionParametersKHR* pVideoSessionParameters) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateVideoSessionParametersKHR(VkDevice device, const VkVideoSessionParametersCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionParametersKHR* pVideoSessionParameters) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateVideoSessionParametersKHR(VkDevice device, const VkVideoSessionParametersCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionParametersKHR* pVideoSessionParameters) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateVideoSessionParametersKHR(VkDevice device, const VkVideoSessionParametersCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionParametersKHR* pVideoSessionParameters) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateVideoSessionParametersKHR(VkDevice device, const VkVideoSessionParametersCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionParametersKHR* pVideoSessionParameters) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateVideoSessionParametersKHR(VkDevice device, const VkVideoSessionParametersCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionParametersKHR* pVideoSessionParameters) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateVideoSessionParametersKHR(VkDevice device, const VkVideoSessionParametersCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionParametersKHR* pVideoSessionParameters) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_UpdateVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkVideoSessionParametersUpdateInfoKHR* pUpdateInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_UpdateVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkVideoSessionParametersUpdateInfoKHR* pUpdateInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_UpdateVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkVideoSessionParametersUpdateInfoKHR* pUpdateInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_UpdateVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkVideoSessionParametersUpdateInfoKHR* pUpdateInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_UpdateVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkVideoSessionParametersUpdateInfoKHR* pUpdateInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_UpdateVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkVideoSessionParametersUpdateInfoKHR* pUpdateInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_UpdateVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkVideoSessionParametersUpdateInfoKHR* pUpdateInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_UpdateVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkVideoSessionParametersUpdateInfoKHR* pUpdateInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetVideoSessionMemoryRequirementsKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t* pMemoryRequirementsCount, VkVideoSessionMemoryRequirementsKHR* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetVideoSessionMemoryRequirementsKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t* pMemoryRequirementsCount, VkVideoSessionMemoryRequirementsKHR* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetVideoSessionMemoryRequirementsKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t* pMemoryRequirementsCount, VkVideoSessionMemoryRequirementsKHR* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetVideoSessionMemoryRequirementsKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t* pMemoryRequirementsCount, VkVideoSessionMemoryRequirementsKHR* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetVideoSessionMemoryRequirementsKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t* pMemoryRequirementsCount, VkVideoSessionMemoryRequirementsKHR* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetVideoSessionMemoryRequirementsKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t* pMemoryRequirementsCount, VkVideoSessionMemoryRequirementsKHR* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetVideoSessionMemoryRequirementsKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t* pMemoryRequirementsCount, VkVideoSessionMemoryRequirementsKHR* pMemoryRequirements) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetVideoSessionMemoryRequirementsKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t* pMemoryRequirementsCount, VkVideoSessionMemoryRequirementsKHR* pMemoryRequirements) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_BindVideoSessionMemoryKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t bindSessionMemoryInfoCount, const VkBindVideoSessionMemoryInfoKHR* pBindSessionMemoryInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_BindVideoSessionMemoryKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t bindSessionMemoryInfoCount, const VkBindVideoSessionMemoryInfoKHR* pBindSessionMemoryInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_BindVideoSessionMemoryKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t bindSessionMemoryInfoCount, const VkBindVideoSessionMemoryInfoKHR* pBindSessionMemoryInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_BindVideoSessionMemoryKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t bindSessionMemoryInfoCount, const VkBindVideoSessionMemoryInfoKHR* pBindSessionMemoryInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_BindVideoSessionMemoryKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t bindSessionMemoryInfoCount, const VkBindVideoSessionMemoryInfoKHR* pBindSessionMemoryInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_BindVideoSessionMemoryKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t bindSessionMemoryInfoCount, const VkBindVideoSessionMemoryInfoKHR* pBindSessionMemoryInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_BindVideoSessionMemoryKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t bindSessionMemoryInfoCount, const VkBindVideoSessionMemoryInfoKHR* pBindSessionMemoryInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_BindVideoSessionMemoryKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t bindSessionMemoryInfoCount, const VkBindVideoSessionMemoryInfoKHR* pBindSessionMemoryInfos) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDecodeVideoKHR(VkCommandBuffer commandBuffer, const VkVideoDecodeInfoKHR* pDecodeInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDecodeVideoKHR(VkCommandBuffer commandBuffer, const VkVideoDecodeInfoKHR* pDecodeInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDecodeVideoKHR(VkCommandBuffer commandBuffer, const VkVideoDecodeInfoKHR* pDecodeInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDecodeVideoKHR(VkCommandBuffer commandBuffer, const VkVideoDecodeInfoKHR* pDecodeInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDecodeVideoKHR(VkCommandBuffer commandBuffer, const VkVideoDecodeInfoKHR* pDecodeInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDecodeVideoKHR(VkCommandBuffer commandBuffer, const VkVideoDecodeInfoKHR* pDecodeInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDecodeVideoKHR(VkCommandBuffer commandBuffer, const VkVideoDecodeInfoKHR* pDecodeInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDecodeVideoKHR(VkCommandBuffer commandBuffer, const VkVideoDecodeInfoKHR* pDecodeInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBeginVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoBeginCodingInfoKHR* pBeginInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBeginVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoBeginCodingInfoKHR* pBeginInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBeginVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoBeginCodingInfoKHR* pBeginInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBeginVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoBeginCodingInfoKHR* pBeginInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBeginVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoBeginCodingInfoKHR* pBeginInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBeginVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoBeginCodingInfoKHR* pBeginInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBeginVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoBeginCodingInfoKHR* pBeginInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBeginVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoBeginCodingInfoKHR* pBeginInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdControlVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoCodingControlInfoKHR* pCodingControlInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdControlVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoCodingControlInfoKHR* pCodingControlInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdControlVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoCodingControlInfoKHR* pCodingControlInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdControlVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoCodingControlInfoKHR* pCodingControlInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdControlVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoCodingControlInfoKHR* pCodingControlInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdControlVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoCodingControlInfoKHR* pCodingControlInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdControlVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoCodingControlInfoKHR* pCodingControlInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdControlVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoCodingControlInfoKHR* pCodingControlInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdEndVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoEndCodingInfoKHR* pEndCodingInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdEndVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoEndCodingInfoKHR* pEndCodingInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdEndVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoEndCodingInfoKHR* pEndCodingInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdEndVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoEndCodingInfoKHR* pEndCodingInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdEndVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoEndCodingInfoKHR* pEndCodingInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdEndVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoEndCodingInfoKHR* pEndCodingInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdEndVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoEndCodingInfoKHR* pEndCodingInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdEndVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoEndCodingInfoKHR* pEndCodingInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDecompressMemoryNV(VkCommandBuffer commandBuffer, uint32_t decompressRegionCount, const VkDecompressMemoryRegionNV* pDecompressMemoryRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDecompressMemoryNV(VkCommandBuffer commandBuffer, uint32_t decompressRegionCount, const VkDecompressMemoryRegionNV* pDecompressMemoryRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDecompressMemoryNV(VkCommandBuffer commandBuffer, uint32_t decompressRegionCount, const VkDecompressMemoryRegionNV* pDecompressMemoryRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDecompressMemoryNV(VkCommandBuffer commandBuffer, uint32_t decompressRegionCount, const VkDecompressMemoryRegionNV* pDecompressMemoryRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDecompressMemoryNV(VkCommandBuffer commandBuffer, uint32_t decompressRegionCount, const VkDecompressMemoryRegionNV* pDecompressMemoryRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDecompressMemoryNV(VkCommandBuffer commandBuffer, uint32_t decompressRegionCount, const VkDecompressMemoryRegionNV* pDecompressMemoryRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDecompressMemoryNV(VkCommandBuffer commandBuffer, uint32_t decompressRegionCount, const VkDecompressMemoryRegionNV* pDecompressMemoryRegions) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDecompressMemoryNV(VkCommandBuffer commandBuffer, uint32_t decompressRegionCount, const VkDecompressMemoryRegionNV* pDecompressMemoryRegions) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdDecompressMemoryIndirectCountNV(VkCommandBuffer commandBuffer, VkDeviceAddress indirectCommandsAddress, VkDeviceAddress indirectCommandsCountAddress, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdDecompressMemoryIndirectCountNV(VkCommandBuffer commandBuffer, VkDeviceAddress indirectCommandsAddress, VkDeviceAddress indirectCommandsCountAddress, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdDecompressMemoryIndirectCountNV(VkCommandBuffer commandBuffer, VkDeviceAddress indirectCommandsAddress, VkDeviceAddress indirectCommandsCountAddress, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdDecompressMemoryIndirectCountNV(VkCommandBuffer commandBuffer, VkDeviceAddress indirectCommandsAddress, VkDeviceAddress indirectCommandsCountAddress, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdDecompressMemoryIndirectCountNV(VkCommandBuffer commandBuffer, VkDeviceAddress indirectCommandsAddress, VkDeviceAddress indirectCommandsCountAddress, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdDecompressMemoryIndirectCountNV(VkCommandBuffer commandBuffer, VkDeviceAddress indirectCommandsAddress, VkDeviceAddress indirectCommandsCountAddress, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdDecompressMemoryIndirectCountNV(VkCommandBuffer commandBuffer, VkDeviceAddress indirectCommandsAddress, VkDeviceAddress indirectCommandsCountAddress, uint32_t stride) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdDecompressMemoryIndirectCountNV(VkCommandBuffer commandBuffer, VkDeviceAddress indirectCommandsAddress, VkDeviceAddress indirectCommandsCountAddress, uint32_t stride) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateCuModuleNVX(VkDevice device, const VkCuModuleCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuModuleNVX* pModule) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateCuModuleNVX(VkDevice device, const VkCuModuleCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuModuleNVX* pModule) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateCuModuleNVX(VkDevice device, const VkCuModuleCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuModuleNVX* pModule) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateCuModuleNVX(VkDevice device, const VkCuModuleCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuModuleNVX* pModule) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateCuModuleNVX(VkDevice device, const VkCuModuleCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuModuleNVX* pModule) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateCuModuleNVX(VkDevice device, const VkCuModuleCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuModuleNVX* pModule) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateCuModuleNVX(VkDevice device, const VkCuModuleCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuModuleNVX* pModule) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateCuModuleNVX(VkDevice device, const VkCuModuleCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuModuleNVX* pModule) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateCuFunctionNVX(VkDevice device, const VkCuFunctionCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuFunctionNVX* pFunction) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateCuFunctionNVX(VkDevice device, const VkCuFunctionCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuFunctionNVX* pFunction) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateCuFunctionNVX(VkDevice device, const VkCuFunctionCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuFunctionNVX* pFunction) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateCuFunctionNVX(VkDevice device, const VkCuFunctionCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuFunctionNVX* pFunction) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateCuFunctionNVX(VkDevice device, const VkCuFunctionCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuFunctionNVX* pFunction) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateCuFunctionNVX(VkDevice device, const VkCuFunctionCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuFunctionNVX* pFunction) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateCuFunctionNVX(VkDevice device, const VkCuFunctionCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuFunctionNVX* pFunction) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateCuFunctionNVX(VkDevice device, const VkCuFunctionCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuFunctionNVX* pFunction) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyCuModuleNVX(VkDevice device, VkCuModuleNVX module, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyCuModuleNVX(VkDevice device, VkCuModuleNVX module, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyCuModuleNVX(VkDevice device, VkCuModuleNVX module, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyCuModuleNVX(VkDevice device, VkCuModuleNVX module, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyCuModuleNVX(VkDevice device, VkCuModuleNVX module, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyCuModuleNVX(VkDevice device, VkCuModuleNVX module, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyCuModuleNVX(VkDevice device, VkCuModuleNVX module, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyCuModuleNVX(VkDevice device, VkCuModuleNVX module, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyCuFunctionNVX(VkDevice device, VkCuFunctionNVX function, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyCuFunctionNVX(VkDevice device, VkCuFunctionNVX function, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyCuFunctionNVX(VkDevice device, VkCuFunctionNVX function, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyCuFunctionNVX(VkDevice device, VkCuFunctionNVX function, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyCuFunctionNVX(VkDevice device, VkCuFunctionNVX function, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyCuFunctionNVX(VkDevice device, VkCuFunctionNVX function, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyCuFunctionNVX(VkDevice device, VkCuFunctionNVX function, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyCuFunctionNVX(VkDevice device, VkCuFunctionNVX function, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCuLaunchKernelNVX(VkCommandBuffer commandBuffer, const VkCuLaunchInfoNVX* pLaunchInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCuLaunchKernelNVX(VkCommandBuffer commandBuffer, const VkCuLaunchInfoNVX* pLaunchInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCuLaunchKernelNVX(VkCommandBuffer commandBuffer, const VkCuLaunchInfoNVX* pLaunchInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCuLaunchKernelNVX(VkCommandBuffer commandBuffer, const VkCuLaunchInfoNVX* pLaunchInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCuLaunchKernelNVX(VkCommandBuffer commandBuffer, const VkCuLaunchInfoNVX* pLaunchInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCuLaunchKernelNVX(VkCommandBuffer commandBuffer, const VkCuLaunchInfoNVX* pLaunchInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCuLaunchKernelNVX(VkCommandBuffer commandBuffer, const VkCuLaunchInfoNVX* pLaunchInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCuLaunchKernelNVX(VkCommandBuffer commandBuffer, const VkCuLaunchInfoNVX* pLaunchInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetDescriptorSetLayoutSizeEXT(VkDevice device, VkDescriptorSetLayout layout, VkDeviceSize* pLayoutSizeInBytes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetDescriptorSetLayoutSizeEXT(VkDevice device, VkDescriptorSetLayout layout, VkDeviceSize* pLayoutSizeInBytes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetDescriptorSetLayoutSizeEXT(VkDevice device, VkDescriptorSetLayout layout, VkDeviceSize* pLayoutSizeInBytes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetDescriptorSetLayoutSizeEXT(VkDevice device, VkDescriptorSetLayout layout, VkDeviceSize* pLayoutSizeInBytes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetDescriptorSetLayoutSizeEXT(VkDevice device, VkDescriptorSetLayout layout, VkDeviceSize* pLayoutSizeInBytes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetDescriptorSetLayoutSizeEXT(VkDevice device, VkDescriptorSetLayout layout, VkDeviceSize* pLayoutSizeInBytes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetDescriptorSetLayoutSizeEXT(VkDevice device, VkDescriptorSetLayout layout, VkDeviceSize* pLayoutSizeInBytes) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetDescriptorSetLayoutSizeEXT(VkDevice device, VkDescriptorSetLayout layout, VkDeviceSize* pLayoutSizeInBytes) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetDescriptorSetLayoutBindingOffsetEXT(VkDevice device, VkDescriptorSetLayout layout, uint32_t binding, VkDeviceSize* pOffset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetDescriptorSetLayoutBindingOffsetEXT(VkDevice device, VkDescriptorSetLayout layout, uint32_t binding, VkDeviceSize* pOffset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetDescriptorSetLayoutBindingOffsetEXT(VkDevice device, VkDescriptorSetLayout layout, uint32_t binding, VkDeviceSize* pOffset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetDescriptorSetLayoutBindingOffsetEXT(VkDevice device, VkDescriptorSetLayout layout, uint32_t binding, VkDeviceSize* pOffset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetDescriptorSetLayoutBindingOffsetEXT(VkDevice device, VkDescriptorSetLayout layout, uint32_t binding, VkDeviceSize* pOffset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetDescriptorSetLayoutBindingOffsetEXT(VkDevice device, VkDescriptorSetLayout layout, uint32_t binding, VkDeviceSize* pOffset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetDescriptorSetLayoutBindingOffsetEXT(VkDevice device, VkDescriptorSetLayout layout, uint32_t binding, VkDeviceSize* pOffset) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetDescriptorSetLayoutBindingOffsetEXT(VkDevice device, VkDescriptorSetLayout layout, uint32_t binding, VkDeviceSize* pOffset) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetDescriptorEXT(VkDevice device, const VkDescriptorGetInfoEXT* pDescriptorInfo, size_t dataSize, void* pDescriptor) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetDescriptorEXT(VkDevice device, const VkDescriptorGetInfoEXT* pDescriptorInfo, size_t dataSize, void* pDescriptor) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetDescriptorEXT(VkDevice device, const VkDescriptorGetInfoEXT* pDescriptorInfo, size_t dataSize, void* pDescriptor) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetDescriptorEXT(VkDevice device, const VkDescriptorGetInfoEXT* pDescriptorInfo, size_t dataSize, void* pDescriptor) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetDescriptorEXT(VkDevice device, const VkDescriptorGetInfoEXT* pDescriptorInfo, size_t dataSize, void* pDescriptor) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetDescriptorEXT(VkDevice device, const VkDescriptorGetInfoEXT* pDescriptorInfo, size_t dataSize, void* pDescriptor) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetDescriptorEXT(VkDevice device, const VkDescriptorGetInfoEXT* pDescriptorInfo, size_t dataSize, void* pDescriptor) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetDescriptorEXT(VkDevice device, const VkDescriptorGetInfoEXT* pDescriptorInfo, size_t dataSize, void* pDescriptor) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBindDescriptorBuffersEXT(VkCommandBuffer commandBuffer, uint32_t bufferCount, const VkDescriptorBufferBindingInfoEXT* pBindingInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBindDescriptorBuffersEXT(VkCommandBuffer commandBuffer, uint32_t bufferCount, const VkDescriptorBufferBindingInfoEXT* pBindingInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBindDescriptorBuffersEXT(VkCommandBuffer commandBuffer, uint32_t bufferCount, const VkDescriptorBufferBindingInfoEXT* pBindingInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBindDescriptorBuffersEXT(VkCommandBuffer commandBuffer, uint32_t bufferCount, const VkDescriptorBufferBindingInfoEXT* pBindingInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBindDescriptorBuffersEXT(VkCommandBuffer commandBuffer, uint32_t bufferCount, const VkDescriptorBufferBindingInfoEXT* pBindingInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBindDescriptorBuffersEXT(VkCommandBuffer commandBuffer, uint32_t bufferCount, const VkDescriptorBufferBindingInfoEXT* pBindingInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBindDescriptorBuffersEXT(VkCommandBuffer commandBuffer, uint32_t bufferCount, const VkDescriptorBufferBindingInfoEXT* pBindingInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBindDescriptorBuffersEXT(VkCommandBuffer commandBuffer, uint32_t bufferCount, const VkDescriptorBufferBindingInfoEXT* pBindingInfos) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdSetDescriptorBufferOffsetsEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t setCount, const uint32_t* pBufferIndices, const VkDeviceSize* pOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdSetDescriptorBufferOffsetsEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t setCount, const uint32_t* pBufferIndices, const VkDeviceSize* pOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdSetDescriptorBufferOffsetsEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t setCount, const uint32_t* pBufferIndices, const VkDeviceSize* pOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdSetDescriptorBufferOffsetsEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t setCount, const uint32_t* pBufferIndices, const VkDeviceSize* pOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdSetDescriptorBufferOffsetsEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t setCount, const uint32_t* pBufferIndices, const VkDeviceSize* pOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdSetDescriptorBufferOffsetsEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t setCount, const uint32_t* pBufferIndices, const VkDeviceSize* pOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdSetDescriptorBufferOffsetsEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t setCount, const uint32_t* pBufferIndices, const VkDeviceSize* pOffsets) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdSetDescriptorBufferOffsetsEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t setCount, const uint32_t* pBufferIndices, const VkDeviceSize* pOffsets) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBindDescriptorBufferEmbeddedSamplersEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBindDescriptorBufferEmbeddedSamplersEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBindDescriptorBufferEmbeddedSamplersEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBindDescriptorBufferEmbeddedSamplersEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBindDescriptorBufferEmbeddedSamplersEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBindDescriptorBufferEmbeddedSamplersEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBindDescriptorBufferEmbeddedSamplersEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBindDescriptorBufferEmbeddedSamplersEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetBufferOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkBufferCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetBufferOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkBufferCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetBufferOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkBufferCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetBufferOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkBufferCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetBufferOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkBufferCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetBufferOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkBufferCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetBufferOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkBufferCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetBufferOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkBufferCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetImageOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetImageOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetImageOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetImageOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetImageOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetImageOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetImageOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetImageOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetImageViewOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageViewCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetImageViewOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageViewCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetImageViewOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageViewCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetImageViewOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageViewCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetImageViewOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageViewCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetImageViewOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageViewCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetImageViewOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageViewCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetImageViewOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageViewCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetSamplerOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkSamplerCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetSamplerOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkSamplerCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetSamplerOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkSamplerCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetSamplerOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkSamplerCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetSamplerOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkSamplerCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetSamplerOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkSamplerCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetSamplerOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkSamplerCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetSamplerOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkSamplerCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetAccelerationStructureOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetAccelerationStructureOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetAccelerationStructureOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetAccelerationStructureOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetAccelerationStructureOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetAccelerationStructureOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetAccelerationStructureOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetAccelerationStructureOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo, void* pData) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_SetDeviceMemoryPriorityEXT(VkDevice       device, VkDeviceMemory memory, float          priority) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_SetDeviceMemoryPriorityEXT(VkDevice       device, VkDeviceMemory memory, float          priority) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_SetDeviceMemoryPriorityEXT(VkDevice       device, VkDeviceMemory memory, float          priority) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_SetDeviceMemoryPriorityEXT(VkDevice       device, VkDeviceMemory memory, float          priority) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_SetDeviceMemoryPriorityEXT(VkDevice       device, VkDeviceMemory memory, float          priority) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_SetDeviceMemoryPriorityEXT(VkDevice       device, VkDeviceMemory memory, float          priority) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_SetDeviceMemoryPriorityEXT(VkDevice       device, VkDeviceMemory memory, float          priority) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_SetDeviceMemoryPriorityEXT(VkDevice       device, VkDeviceMemory memory, float          priority) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_WaitForPresentKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t presentId, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_WaitForPresentKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t presentId, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_WaitForPresentKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t presentId, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_WaitForPresentKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t presentId, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_WaitForPresentKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t presentId, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_WaitForPresentKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t presentId, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_WaitForPresentKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t presentId, uint64_t timeout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_WaitForPresentKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t presentId, uint64_t timeout) ATTR_WEAK;


#ifdef VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateBufferCollectionFUCHSIA(VkDevice device, const VkBufferCollectionCreateInfoFUCHSIA* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferCollectionFUCHSIA* pCollection) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateBufferCollectionFUCHSIA(VkDevice device, const VkBufferCollectionCreateInfoFUCHSIA* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferCollectionFUCHSIA* pCollection) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateBufferCollectionFUCHSIA(VkDevice device, const VkBufferCollectionCreateInfoFUCHSIA* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferCollectionFUCHSIA* pCollection) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateBufferCollectionFUCHSIA(VkDevice device, const VkBufferCollectionCreateInfoFUCHSIA* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferCollectionFUCHSIA* pCollection) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateBufferCollectionFUCHSIA(VkDevice device, const VkBufferCollectionCreateInfoFUCHSIA* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferCollectionFUCHSIA* pCollection) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateBufferCollectionFUCHSIA(VkDevice device, const VkBufferCollectionCreateInfoFUCHSIA* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferCollectionFUCHSIA* pCollection) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateBufferCollectionFUCHSIA(VkDevice device, const VkBufferCollectionCreateInfoFUCHSIA* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferCollectionFUCHSIA* pCollection) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateBufferCollectionFUCHSIA(VkDevice device, const VkBufferCollectionCreateInfoFUCHSIA* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferCollectionFUCHSIA* pCollection) ATTR_WEAK;


#endif // VK_USE_PLATFORM_FUCHSIA
#ifdef VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR VkResult VKAPI_CALL anv_SetBufferCollectionBufferConstraintsFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkBufferConstraintsInfoFUCHSIA* pBufferConstraintsInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_SetBufferCollectionBufferConstraintsFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkBufferConstraintsInfoFUCHSIA* pBufferConstraintsInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_SetBufferCollectionBufferConstraintsFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkBufferConstraintsInfoFUCHSIA* pBufferConstraintsInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_SetBufferCollectionBufferConstraintsFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkBufferConstraintsInfoFUCHSIA* pBufferConstraintsInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_SetBufferCollectionBufferConstraintsFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkBufferConstraintsInfoFUCHSIA* pBufferConstraintsInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_SetBufferCollectionBufferConstraintsFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkBufferConstraintsInfoFUCHSIA* pBufferConstraintsInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_SetBufferCollectionBufferConstraintsFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkBufferConstraintsInfoFUCHSIA* pBufferConstraintsInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_SetBufferCollectionBufferConstraintsFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkBufferConstraintsInfoFUCHSIA* pBufferConstraintsInfo) ATTR_WEAK;


#endif // VK_USE_PLATFORM_FUCHSIA
#ifdef VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR VkResult VKAPI_CALL anv_SetBufferCollectionImageConstraintsFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_SetBufferCollectionImageConstraintsFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_SetBufferCollectionImageConstraintsFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_SetBufferCollectionImageConstraintsFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_SetBufferCollectionImageConstraintsFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_SetBufferCollectionImageConstraintsFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_SetBufferCollectionImageConstraintsFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_SetBufferCollectionImageConstraintsFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo) ATTR_WEAK;


#endif // VK_USE_PLATFORM_FUCHSIA
#ifdef VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR void VKAPI_CALL anv_DestroyBufferCollectionFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyBufferCollectionFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyBufferCollectionFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyBufferCollectionFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyBufferCollectionFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyBufferCollectionFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyBufferCollectionFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyBufferCollectionFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


#endif // VK_USE_PLATFORM_FUCHSIA
#ifdef VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetBufferCollectionPropertiesFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, VkBufferCollectionPropertiesFUCHSIA* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetBufferCollectionPropertiesFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, VkBufferCollectionPropertiesFUCHSIA* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetBufferCollectionPropertiesFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, VkBufferCollectionPropertiesFUCHSIA* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetBufferCollectionPropertiesFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, VkBufferCollectionPropertiesFUCHSIA* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetBufferCollectionPropertiesFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, VkBufferCollectionPropertiesFUCHSIA* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetBufferCollectionPropertiesFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, VkBufferCollectionPropertiesFUCHSIA* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetBufferCollectionPropertiesFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, VkBufferCollectionPropertiesFUCHSIA* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetBufferCollectionPropertiesFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, VkBufferCollectionPropertiesFUCHSIA* pProperties) ATTR_WEAK;


#endif // VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR void VKAPI_CALL anv_CmdBeginRendering(VkCommandBuffer                   commandBuffer, const VkRenderingInfo*                              pRenderingInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBeginRendering(VkCommandBuffer                   commandBuffer, const VkRenderingInfo*                              pRenderingInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBeginRendering(VkCommandBuffer                   commandBuffer, const VkRenderingInfo*                              pRenderingInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBeginRendering(VkCommandBuffer                   commandBuffer, const VkRenderingInfo*                              pRenderingInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBeginRendering(VkCommandBuffer                   commandBuffer, const VkRenderingInfo*                              pRenderingInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBeginRendering(VkCommandBuffer                   commandBuffer, const VkRenderingInfo*                              pRenderingInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBeginRendering(VkCommandBuffer                   commandBuffer, const VkRenderingInfo*                              pRenderingInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBeginRendering(VkCommandBuffer                   commandBuffer, const VkRenderingInfo*                              pRenderingInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBeginRenderingKHR(VkCommandBuffer                   commandBuffer, const VkRenderingInfo*                              pRenderingInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBeginRenderingKHR(VkCommandBuffer                   commandBuffer, const VkRenderingInfo*                              pRenderingInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBeginRenderingKHR(VkCommandBuffer                   commandBuffer, const VkRenderingInfo*                              pRenderingInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBeginRenderingKHR(VkCommandBuffer                   commandBuffer, const VkRenderingInfo*                              pRenderingInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBeginRenderingKHR(VkCommandBuffer                   commandBuffer, const VkRenderingInfo*                              pRenderingInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBeginRenderingKHR(VkCommandBuffer                   commandBuffer, const VkRenderingInfo*                              pRenderingInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBeginRenderingKHR(VkCommandBuffer                   commandBuffer, const VkRenderingInfo*                              pRenderingInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBeginRenderingKHR(VkCommandBuffer                   commandBuffer, const VkRenderingInfo*                              pRenderingInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdEndRendering(VkCommandBuffer                   commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdEndRendering(VkCommandBuffer                   commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdEndRendering(VkCommandBuffer                   commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdEndRendering(VkCommandBuffer                   commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdEndRendering(VkCommandBuffer                   commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdEndRendering(VkCommandBuffer                   commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdEndRendering(VkCommandBuffer                   commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdEndRendering(VkCommandBuffer                   commandBuffer) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdEndRenderingKHR(VkCommandBuffer                   commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdEndRenderingKHR(VkCommandBuffer                   commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdEndRenderingKHR(VkCommandBuffer                   commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdEndRenderingKHR(VkCommandBuffer                   commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdEndRenderingKHR(VkCommandBuffer                   commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdEndRenderingKHR(VkCommandBuffer                   commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdEndRenderingKHR(VkCommandBuffer                   commandBuffer) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdEndRenderingKHR(VkCommandBuffer                   commandBuffer) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetDescriptorSetLayoutHostMappingInfoVALVE(VkDevice device, const VkDescriptorSetBindingReferenceVALVE* pBindingReference, VkDescriptorSetLayoutHostMappingInfoVALVE* pHostMapping) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetDescriptorSetLayoutHostMappingInfoVALVE(VkDevice device, const VkDescriptorSetBindingReferenceVALVE* pBindingReference, VkDescriptorSetLayoutHostMappingInfoVALVE* pHostMapping) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetDescriptorSetLayoutHostMappingInfoVALVE(VkDevice device, const VkDescriptorSetBindingReferenceVALVE* pBindingReference, VkDescriptorSetLayoutHostMappingInfoVALVE* pHostMapping) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetDescriptorSetLayoutHostMappingInfoVALVE(VkDevice device, const VkDescriptorSetBindingReferenceVALVE* pBindingReference, VkDescriptorSetLayoutHostMappingInfoVALVE* pHostMapping) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetDescriptorSetLayoutHostMappingInfoVALVE(VkDevice device, const VkDescriptorSetBindingReferenceVALVE* pBindingReference, VkDescriptorSetLayoutHostMappingInfoVALVE* pHostMapping) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetDescriptorSetLayoutHostMappingInfoVALVE(VkDevice device, const VkDescriptorSetBindingReferenceVALVE* pBindingReference, VkDescriptorSetLayoutHostMappingInfoVALVE* pHostMapping) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetDescriptorSetLayoutHostMappingInfoVALVE(VkDevice device, const VkDescriptorSetBindingReferenceVALVE* pBindingReference, VkDescriptorSetLayoutHostMappingInfoVALVE* pHostMapping) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetDescriptorSetLayoutHostMappingInfoVALVE(VkDevice device, const VkDescriptorSetBindingReferenceVALVE* pBindingReference, VkDescriptorSetLayoutHostMappingInfoVALVE* pHostMapping) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetDescriptorSetHostMappingVALVE(VkDevice device, VkDescriptorSet descriptorSet, void** ppData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetDescriptorSetHostMappingVALVE(VkDevice device, VkDescriptorSet descriptorSet, void** ppData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetDescriptorSetHostMappingVALVE(VkDevice device, VkDescriptorSet descriptorSet, void** ppData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetDescriptorSetHostMappingVALVE(VkDevice device, VkDescriptorSet descriptorSet, void** ppData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetDescriptorSetHostMappingVALVE(VkDevice device, VkDescriptorSet descriptorSet, void** ppData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetDescriptorSetHostMappingVALVE(VkDevice device, VkDescriptorSet descriptorSet, void** ppData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetDescriptorSetHostMappingVALVE(VkDevice device, VkDescriptorSet descriptorSet, void** ppData) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetDescriptorSetHostMappingVALVE(VkDevice device, VkDescriptorSet descriptorSet, void** ppData) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateMicromapEXT(VkDevice                                           device, const VkMicromapCreateInfoEXT*        pCreateInfo, const VkAllocationCallbacks*       pAllocator, VkMicromapEXT*                        pMicromap) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateMicromapEXT(VkDevice                                           device, const VkMicromapCreateInfoEXT*        pCreateInfo, const VkAllocationCallbacks*       pAllocator, VkMicromapEXT*                        pMicromap) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateMicromapEXT(VkDevice                                           device, const VkMicromapCreateInfoEXT*        pCreateInfo, const VkAllocationCallbacks*       pAllocator, VkMicromapEXT*                        pMicromap) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateMicromapEXT(VkDevice                                           device, const VkMicromapCreateInfoEXT*        pCreateInfo, const VkAllocationCallbacks*       pAllocator, VkMicromapEXT*                        pMicromap) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateMicromapEXT(VkDevice                                           device, const VkMicromapCreateInfoEXT*        pCreateInfo, const VkAllocationCallbacks*       pAllocator, VkMicromapEXT*                        pMicromap) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateMicromapEXT(VkDevice                                           device, const VkMicromapCreateInfoEXT*        pCreateInfo, const VkAllocationCallbacks*       pAllocator, VkMicromapEXT*                        pMicromap) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateMicromapEXT(VkDevice                                           device, const VkMicromapCreateInfoEXT*        pCreateInfo, const VkAllocationCallbacks*       pAllocator, VkMicromapEXT*                        pMicromap) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateMicromapEXT(VkDevice                                           device, const VkMicromapCreateInfoEXT*        pCreateInfo, const VkAllocationCallbacks*       pAllocator, VkMicromapEXT*                        pMicromap) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBuildMicromapsEXT(VkCommandBuffer                                    commandBuffer, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBuildMicromapsEXT(VkCommandBuffer                                    commandBuffer, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBuildMicromapsEXT(VkCommandBuffer                                    commandBuffer, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBuildMicromapsEXT(VkCommandBuffer                                    commandBuffer, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBuildMicromapsEXT(VkCommandBuffer                                    commandBuffer, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBuildMicromapsEXT(VkCommandBuffer                                    commandBuffer, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBuildMicromapsEXT(VkCommandBuffer                                    commandBuffer, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBuildMicromapsEXT(VkCommandBuffer                                    commandBuffer, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_BuildMicromapsEXT(VkDevice                                           device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_BuildMicromapsEXT(VkDevice                                           device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_BuildMicromapsEXT(VkDevice                                           device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_BuildMicromapsEXT(VkDevice                                           device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_BuildMicromapsEXT(VkDevice                                           device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_BuildMicromapsEXT(VkDevice                                           device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_BuildMicromapsEXT(VkDevice                                           device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_BuildMicromapsEXT(VkDevice                                           device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyMicromapEXT(VkDevice device, VkMicromapEXT micromap, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyMicromapEXT(VkDevice device, VkMicromapEXT micromap, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyMicromapEXT(VkDevice device, VkMicromapEXT micromap, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyMicromapEXT(VkDevice device, VkMicromapEXT micromap, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyMicromapEXT(VkDevice device, VkMicromapEXT micromap, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyMicromapEXT(VkDevice device, VkMicromapEXT micromap, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyMicromapEXT(VkDevice device, VkMicromapEXT micromap, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyMicromapEXT(VkDevice device, VkMicromapEXT micromap, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCopyMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCopyMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCopyMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCopyMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCopyMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCopyMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCopyMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCopyMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapInfoEXT* pInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CopyMicromapEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CopyMicromapEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CopyMicromapEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CopyMicromapEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CopyMicromapEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CopyMicromapEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CopyMicromapEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CopyMicromapEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapInfoEXT* pInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCopyMicromapToMemoryEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapToMemoryInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCopyMicromapToMemoryEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapToMemoryInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCopyMicromapToMemoryEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapToMemoryInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCopyMicromapToMemoryEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapToMemoryInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCopyMicromapToMemoryEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapToMemoryInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCopyMicromapToMemoryEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapToMemoryInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCopyMicromapToMemoryEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapToMemoryInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCopyMicromapToMemoryEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapToMemoryInfoEXT* pInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CopyMicromapToMemoryEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapToMemoryInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CopyMicromapToMemoryEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapToMemoryInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CopyMicromapToMemoryEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapToMemoryInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CopyMicromapToMemoryEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapToMemoryInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CopyMicromapToMemoryEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapToMemoryInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CopyMicromapToMemoryEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapToMemoryInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CopyMicromapToMemoryEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapToMemoryInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CopyMicromapToMemoryEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapToMemoryInfoEXT* pInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdCopyMemoryToMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMemoryToMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdCopyMemoryToMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMemoryToMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdCopyMemoryToMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMemoryToMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdCopyMemoryToMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMemoryToMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdCopyMemoryToMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMemoryToMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdCopyMemoryToMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMemoryToMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdCopyMemoryToMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMemoryToMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdCopyMemoryToMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMemoryToMicromapInfoEXT* pInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CopyMemoryToMicromapEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CopyMemoryToMicromapEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CopyMemoryToMicromapEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CopyMemoryToMicromapEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CopyMemoryToMicromapEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CopyMemoryToMicromapEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CopyMemoryToMicromapEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToMicromapInfoEXT* pInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CopyMemoryToMicromapEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToMicromapInfoEXT* pInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdWriteMicromapsPropertiesEXT(VkCommandBuffer commandBuffer, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdWriteMicromapsPropertiesEXT(VkCommandBuffer commandBuffer, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdWriteMicromapsPropertiesEXT(VkCommandBuffer commandBuffer, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdWriteMicromapsPropertiesEXT(VkCommandBuffer commandBuffer, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdWriteMicromapsPropertiesEXT(VkCommandBuffer commandBuffer, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdWriteMicromapsPropertiesEXT(VkCommandBuffer commandBuffer, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdWriteMicromapsPropertiesEXT(VkCommandBuffer commandBuffer, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdWriteMicromapsPropertiesEXT(VkCommandBuffer commandBuffer, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_WriteMicromapsPropertiesEXT(VkDevice device, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType  queryType, size_t       dataSize, void* pData, size_t stride) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_WriteMicromapsPropertiesEXT(VkDevice device, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType  queryType, size_t       dataSize, void* pData, size_t stride) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_WriteMicromapsPropertiesEXT(VkDevice device, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType  queryType, size_t       dataSize, void* pData, size_t stride) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_WriteMicromapsPropertiesEXT(VkDevice device, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType  queryType, size_t       dataSize, void* pData, size_t stride) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_WriteMicromapsPropertiesEXT(VkDevice device, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType  queryType, size_t       dataSize, void* pData, size_t stride) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_WriteMicromapsPropertiesEXT(VkDevice device, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType  queryType, size_t       dataSize, void* pData, size_t stride) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_WriteMicromapsPropertiesEXT(VkDevice device, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType  queryType, size_t       dataSize, void* pData, size_t stride) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_WriteMicromapsPropertiesEXT(VkDevice device, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType  queryType, size_t       dataSize, void* pData, size_t stride) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetDeviceMicromapCompatibilityEXT(VkDevice device, const VkMicromapVersionInfoEXT* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetDeviceMicromapCompatibilityEXT(VkDevice device, const VkMicromapVersionInfoEXT* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetDeviceMicromapCompatibilityEXT(VkDevice device, const VkMicromapVersionInfoEXT* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetDeviceMicromapCompatibilityEXT(VkDevice device, const VkMicromapVersionInfoEXT* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetDeviceMicromapCompatibilityEXT(VkDevice device, const VkMicromapVersionInfoEXT* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetDeviceMicromapCompatibilityEXT(VkDevice device, const VkMicromapVersionInfoEXT* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetDeviceMicromapCompatibilityEXT(VkDevice device, const VkMicromapVersionInfoEXT* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetDeviceMicromapCompatibilityEXT(VkDevice device, const VkMicromapVersionInfoEXT* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetMicromapBuildSizesEXT(VkDevice                                            device, VkAccelerationStructureBuildTypeKHR                 buildType, const VkMicromapBuildInfoEXT*  pBuildInfo, VkMicromapBuildSizesInfoEXT*           pSizeInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetMicromapBuildSizesEXT(VkDevice                                            device, VkAccelerationStructureBuildTypeKHR                 buildType, const VkMicromapBuildInfoEXT*  pBuildInfo, VkMicromapBuildSizesInfoEXT*           pSizeInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetMicromapBuildSizesEXT(VkDevice                                            device, VkAccelerationStructureBuildTypeKHR                 buildType, const VkMicromapBuildInfoEXT*  pBuildInfo, VkMicromapBuildSizesInfoEXT*           pSizeInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetMicromapBuildSizesEXT(VkDevice                                            device, VkAccelerationStructureBuildTypeKHR                 buildType, const VkMicromapBuildInfoEXT*  pBuildInfo, VkMicromapBuildSizesInfoEXT*           pSizeInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetMicromapBuildSizesEXT(VkDevice                                            device, VkAccelerationStructureBuildTypeKHR                 buildType, const VkMicromapBuildInfoEXT*  pBuildInfo, VkMicromapBuildSizesInfoEXT*           pSizeInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetMicromapBuildSizesEXT(VkDevice                                            device, VkAccelerationStructureBuildTypeKHR                 buildType, const VkMicromapBuildInfoEXT*  pBuildInfo, VkMicromapBuildSizesInfoEXT*           pSizeInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetMicromapBuildSizesEXT(VkDevice                                            device, VkAccelerationStructureBuildTypeKHR                 buildType, const VkMicromapBuildInfoEXT*  pBuildInfo, VkMicromapBuildSizesInfoEXT*           pSizeInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetMicromapBuildSizesEXT(VkDevice                                            device, VkAccelerationStructureBuildTypeKHR                 buildType, const VkMicromapBuildInfoEXT*  pBuildInfo, VkMicromapBuildSizesInfoEXT*           pSizeInfo) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetShaderModuleIdentifierEXT(VkDevice device, VkShaderModule shaderModule, VkShaderModuleIdentifierEXT* pIdentifier) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetShaderModuleIdentifierEXT(VkDevice device, VkShaderModule shaderModule, VkShaderModuleIdentifierEXT* pIdentifier) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetShaderModuleIdentifierEXT(VkDevice device, VkShaderModule shaderModule, VkShaderModuleIdentifierEXT* pIdentifier) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetShaderModuleIdentifierEXT(VkDevice device, VkShaderModule shaderModule, VkShaderModuleIdentifierEXT* pIdentifier) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetShaderModuleIdentifierEXT(VkDevice device, VkShaderModule shaderModule, VkShaderModuleIdentifierEXT* pIdentifier) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetShaderModuleIdentifierEXT(VkDevice device, VkShaderModule shaderModule, VkShaderModuleIdentifierEXT* pIdentifier) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetShaderModuleIdentifierEXT(VkDevice device, VkShaderModule shaderModule, VkShaderModuleIdentifierEXT* pIdentifier) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetShaderModuleIdentifierEXT(VkDevice device, VkShaderModule shaderModule, VkShaderModuleIdentifierEXT* pIdentifier) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetShaderModuleCreateInfoIdentifierEXT(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, VkShaderModuleIdentifierEXT* pIdentifier) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetShaderModuleCreateInfoIdentifierEXT(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, VkShaderModuleIdentifierEXT* pIdentifier) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetShaderModuleCreateInfoIdentifierEXT(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, VkShaderModuleIdentifierEXT* pIdentifier) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetShaderModuleCreateInfoIdentifierEXT(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, VkShaderModuleIdentifierEXT* pIdentifier) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetShaderModuleCreateInfoIdentifierEXT(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, VkShaderModuleIdentifierEXT* pIdentifier) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetShaderModuleCreateInfoIdentifierEXT(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, VkShaderModuleIdentifierEXT* pIdentifier) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetShaderModuleCreateInfoIdentifierEXT(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, VkShaderModuleIdentifierEXT* pIdentifier) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetShaderModuleCreateInfoIdentifierEXT(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, VkShaderModuleIdentifierEXT* pIdentifier) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_GetImageSubresourceLayout2EXT(VkDevice device, VkImage image, const VkImageSubresource2EXT* pSubresource, VkSubresourceLayout2EXT* pLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_GetImageSubresourceLayout2EXT(VkDevice device, VkImage image, const VkImageSubresource2EXT* pSubresource, VkSubresourceLayout2EXT* pLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_GetImageSubresourceLayout2EXT(VkDevice device, VkImage image, const VkImageSubresource2EXT* pSubresource, VkSubresourceLayout2EXT* pLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_GetImageSubresourceLayout2EXT(VkDevice device, VkImage image, const VkImageSubresource2EXT* pSubresource, VkSubresourceLayout2EXT* pLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_GetImageSubresourceLayout2EXT(VkDevice device, VkImage image, const VkImageSubresource2EXT* pSubresource, VkSubresourceLayout2EXT* pLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_GetImageSubresourceLayout2EXT(VkDevice device, VkImage image, const VkImageSubresource2EXT* pSubresource, VkSubresourceLayout2EXT* pLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_GetImageSubresourceLayout2EXT(VkDevice device, VkImage image, const VkImageSubresource2EXT* pSubresource, VkSubresourceLayout2EXT* pLayout) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_GetImageSubresourceLayout2EXT(VkDevice device, VkImage image, const VkImageSubresource2EXT* pSubresource, VkSubresourceLayout2EXT* pLayout) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetPipelinePropertiesEXT(VkDevice device, const VkPipelineInfoEXT* pPipelineInfo, VkBaseOutStructure* pPipelineProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetPipelinePropertiesEXT(VkDevice device, const VkPipelineInfoEXT* pPipelineInfo, VkBaseOutStructure* pPipelineProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetPipelinePropertiesEXT(VkDevice device, const VkPipelineInfoEXT* pPipelineInfo, VkBaseOutStructure* pPipelineProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetPipelinePropertiesEXT(VkDevice device, const VkPipelineInfoEXT* pPipelineInfo, VkBaseOutStructure* pPipelineProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetPipelinePropertiesEXT(VkDevice device, const VkPipelineInfoEXT* pPipelineInfo, VkBaseOutStructure* pPipelineProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetPipelinePropertiesEXT(VkDevice device, const VkPipelineInfoEXT* pPipelineInfo, VkBaseOutStructure* pPipelineProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetPipelinePropertiesEXT(VkDevice device, const VkPipelineInfoEXT* pPipelineInfo, VkBaseOutStructure* pPipelineProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetPipelinePropertiesEXT(VkDevice device, const VkPipelineInfoEXT* pPipelineInfo, VkBaseOutStructure* pPipelineProperties) ATTR_WEAK;


#ifdef VK_USE_PLATFORM_METAL_EXT
  VKAPI_ATTR void VKAPI_CALL anv_ExportMetalObjectsEXT(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_ExportMetalObjectsEXT(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_ExportMetalObjectsEXT(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_ExportMetalObjectsEXT(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_ExportMetalObjectsEXT(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_ExportMetalObjectsEXT(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_ExportMetalObjectsEXT(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_ExportMetalObjectsEXT(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo) ATTR_WEAK;


#endif // VK_USE_PLATFORM_METAL_EXT
  VKAPI_ATTR VkResult VKAPI_CALL anv_GetFramebufferTilePropertiesQCOM(VkDevice device, VkFramebuffer framebuffer, uint32_t* pPropertiesCount, VkTilePropertiesQCOM* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetFramebufferTilePropertiesQCOM(VkDevice device, VkFramebuffer framebuffer, uint32_t* pPropertiesCount, VkTilePropertiesQCOM* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetFramebufferTilePropertiesQCOM(VkDevice device, VkFramebuffer framebuffer, uint32_t* pPropertiesCount, VkTilePropertiesQCOM* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetFramebufferTilePropertiesQCOM(VkDevice device, VkFramebuffer framebuffer, uint32_t* pPropertiesCount, VkTilePropertiesQCOM* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetFramebufferTilePropertiesQCOM(VkDevice device, VkFramebuffer framebuffer, uint32_t* pPropertiesCount, VkTilePropertiesQCOM* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetFramebufferTilePropertiesQCOM(VkDevice device, VkFramebuffer framebuffer, uint32_t* pPropertiesCount, VkTilePropertiesQCOM* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetFramebufferTilePropertiesQCOM(VkDevice device, VkFramebuffer framebuffer, uint32_t* pPropertiesCount, VkTilePropertiesQCOM* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetFramebufferTilePropertiesQCOM(VkDevice device, VkFramebuffer framebuffer, uint32_t* pPropertiesCount, VkTilePropertiesQCOM* pProperties) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetDynamicRenderingTilePropertiesQCOM(VkDevice device, const VkRenderingInfo* pRenderingInfo, VkTilePropertiesQCOM* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetDynamicRenderingTilePropertiesQCOM(VkDevice device, const VkRenderingInfo* pRenderingInfo, VkTilePropertiesQCOM* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetDynamicRenderingTilePropertiesQCOM(VkDevice device, const VkRenderingInfo* pRenderingInfo, VkTilePropertiesQCOM* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetDynamicRenderingTilePropertiesQCOM(VkDevice device, const VkRenderingInfo* pRenderingInfo, VkTilePropertiesQCOM* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetDynamicRenderingTilePropertiesQCOM(VkDevice device, const VkRenderingInfo* pRenderingInfo, VkTilePropertiesQCOM* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetDynamicRenderingTilePropertiesQCOM(VkDevice device, const VkRenderingInfo* pRenderingInfo, VkTilePropertiesQCOM* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetDynamicRenderingTilePropertiesQCOM(VkDevice device, const VkRenderingInfo* pRenderingInfo, VkTilePropertiesQCOM* pProperties) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetDynamicRenderingTilePropertiesQCOM(VkDevice device, const VkRenderingInfo* pRenderingInfo, VkTilePropertiesQCOM* pProperties) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateOpticalFlowSessionNV(VkDevice device, const VkOpticalFlowSessionCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkOpticalFlowSessionNV* pSession) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateOpticalFlowSessionNV(VkDevice device, const VkOpticalFlowSessionCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkOpticalFlowSessionNV* pSession) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateOpticalFlowSessionNV(VkDevice device, const VkOpticalFlowSessionCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkOpticalFlowSessionNV* pSession) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateOpticalFlowSessionNV(VkDevice device, const VkOpticalFlowSessionCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkOpticalFlowSessionNV* pSession) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateOpticalFlowSessionNV(VkDevice device, const VkOpticalFlowSessionCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkOpticalFlowSessionNV* pSession) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateOpticalFlowSessionNV(VkDevice device, const VkOpticalFlowSessionCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkOpticalFlowSessionNV* pSession) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateOpticalFlowSessionNV(VkDevice device, const VkOpticalFlowSessionCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkOpticalFlowSessionNV* pSession) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateOpticalFlowSessionNV(VkDevice device, const VkOpticalFlowSessionCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkOpticalFlowSessionNV* pSession) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyOpticalFlowSessionNV(VkDevice device, VkOpticalFlowSessionNV session, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyOpticalFlowSessionNV(VkDevice device, VkOpticalFlowSessionNV session, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyOpticalFlowSessionNV(VkDevice device, VkOpticalFlowSessionNV session, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyOpticalFlowSessionNV(VkDevice device, VkOpticalFlowSessionNV session, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyOpticalFlowSessionNV(VkDevice device, VkOpticalFlowSessionNV session, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyOpticalFlowSessionNV(VkDevice device, VkOpticalFlowSessionNV session, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyOpticalFlowSessionNV(VkDevice device, VkOpticalFlowSessionNV session, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyOpticalFlowSessionNV(VkDevice device, VkOpticalFlowSessionNV session, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_BindOpticalFlowSessionImageNV(VkDevice device, VkOpticalFlowSessionNV session, VkOpticalFlowSessionBindingPointNV bindingPoint, VkImageView view, VkImageLayout layout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_BindOpticalFlowSessionImageNV(VkDevice device, VkOpticalFlowSessionNV session, VkOpticalFlowSessionBindingPointNV bindingPoint, VkImageView view, VkImageLayout layout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_BindOpticalFlowSessionImageNV(VkDevice device, VkOpticalFlowSessionNV session, VkOpticalFlowSessionBindingPointNV bindingPoint, VkImageView view, VkImageLayout layout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_BindOpticalFlowSessionImageNV(VkDevice device, VkOpticalFlowSessionNV session, VkOpticalFlowSessionBindingPointNV bindingPoint, VkImageView view, VkImageLayout layout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_BindOpticalFlowSessionImageNV(VkDevice device, VkOpticalFlowSessionNV session, VkOpticalFlowSessionBindingPointNV bindingPoint, VkImageView view, VkImageLayout layout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_BindOpticalFlowSessionImageNV(VkDevice device, VkOpticalFlowSessionNV session, VkOpticalFlowSessionBindingPointNV bindingPoint, VkImageView view, VkImageLayout layout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_BindOpticalFlowSessionImageNV(VkDevice device, VkOpticalFlowSessionNV session, VkOpticalFlowSessionBindingPointNV bindingPoint, VkImageView view, VkImageLayout layout) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_BindOpticalFlowSessionImageNV(VkDevice device, VkOpticalFlowSessionNV session, VkOpticalFlowSessionBindingPointNV bindingPoint, VkImageView view, VkImageLayout layout) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdOpticalFlowExecuteNV(VkCommandBuffer commandBuffer, VkOpticalFlowSessionNV session, const VkOpticalFlowExecuteInfoNV* pExecuteInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdOpticalFlowExecuteNV(VkCommandBuffer commandBuffer, VkOpticalFlowSessionNV session, const VkOpticalFlowExecuteInfoNV* pExecuteInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdOpticalFlowExecuteNV(VkCommandBuffer commandBuffer, VkOpticalFlowSessionNV session, const VkOpticalFlowExecuteInfoNV* pExecuteInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdOpticalFlowExecuteNV(VkCommandBuffer commandBuffer, VkOpticalFlowSessionNV session, const VkOpticalFlowExecuteInfoNV* pExecuteInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdOpticalFlowExecuteNV(VkCommandBuffer commandBuffer, VkOpticalFlowSessionNV session, const VkOpticalFlowExecuteInfoNV* pExecuteInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdOpticalFlowExecuteNV(VkCommandBuffer commandBuffer, VkOpticalFlowSessionNV session, const VkOpticalFlowExecuteInfoNV* pExecuteInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdOpticalFlowExecuteNV(VkCommandBuffer commandBuffer, VkOpticalFlowSessionNV session, const VkOpticalFlowExecuteInfoNV* pExecuteInfo) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdOpticalFlowExecuteNV(VkCommandBuffer commandBuffer, VkOpticalFlowSessionNV session, const VkOpticalFlowExecuteInfoNV* pExecuteInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetDeviceFaultInfoEXT(VkDevice device, VkDeviceFaultCountsEXT* pFaultCounts, VkDeviceFaultInfoEXT* pFaultInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetDeviceFaultInfoEXT(VkDevice device, VkDeviceFaultCountsEXT* pFaultCounts, VkDeviceFaultInfoEXT* pFaultInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetDeviceFaultInfoEXT(VkDevice device, VkDeviceFaultCountsEXT* pFaultCounts, VkDeviceFaultInfoEXT* pFaultInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetDeviceFaultInfoEXT(VkDevice device, VkDeviceFaultCountsEXT* pFaultCounts, VkDeviceFaultInfoEXT* pFaultInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetDeviceFaultInfoEXT(VkDevice device, VkDeviceFaultCountsEXT* pFaultCounts, VkDeviceFaultInfoEXT* pFaultInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetDeviceFaultInfoEXT(VkDevice device, VkDeviceFaultCountsEXT* pFaultCounts, VkDeviceFaultInfoEXT* pFaultInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetDeviceFaultInfoEXT(VkDevice device, VkDeviceFaultCountsEXT* pFaultCounts, VkDeviceFaultInfoEXT* pFaultInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetDeviceFaultInfoEXT(VkDevice device, VkDeviceFaultCountsEXT* pFaultCounts, VkDeviceFaultInfoEXT* pFaultInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_ReleaseSwapchainImagesEXT(VkDevice device, const VkReleaseSwapchainImagesInfoEXT* pReleaseInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_ReleaseSwapchainImagesEXT(VkDevice device, const VkReleaseSwapchainImagesInfoEXT* pReleaseInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_ReleaseSwapchainImagesEXT(VkDevice device, const VkReleaseSwapchainImagesInfoEXT* pReleaseInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_ReleaseSwapchainImagesEXT(VkDevice device, const VkReleaseSwapchainImagesInfoEXT* pReleaseInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_ReleaseSwapchainImagesEXT(VkDevice device, const VkReleaseSwapchainImagesInfoEXT* pReleaseInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_ReleaseSwapchainImagesEXT(VkDevice device, const VkReleaseSwapchainImagesInfoEXT* pReleaseInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_ReleaseSwapchainImagesEXT(VkDevice device, const VkReleaseSwapchainImagesInfoEXT* pReleaseInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_ReleaseSwapchainImagesEXT(VkDevice device, const VkReleaseSwapchainImagesInfoEXT* pReleaseInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_MapMemory2KHR(VkDevice device, const VkMemoryMapInfoKHR* pMemoryMapInfo, void** ppData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_MapMemory2KHR(VkDevice device, const VkMemoryMapInfoKHR* pMemoryMapInfo, void** ppData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_MapMemory2KHR(VkDevice device, const VkMemoryMapInfoKHR* pMemoryMapInfo, void** ppData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_MapMemory2KHR(VkDevice device, const VkMemoryMapInfoKHR* pMemoryMapInfo, void** ppData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_MapMemory2KHR(VkDevice device, const VkMemoryMapInfoKHR* pMemoryMapInfo, void** ppData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_MapMemory2KHR(VkDevice device, const VkMemoryMapInfoKHR* pMemoryMapInfo, void** ppData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_MapMemory2KHR(VkDevice device, const VkMemoryMapInfoKHR* pMemoryMapInfo, void** ppData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_MapMemory2KHR(VkDevice device, const VkMemoryMapInfoKHR* pMemoryMapInfo, void** ppData) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_UnmapMemory2KHR(VkDevice device, const VkMemoryUnmapInfoKHR* pMemoryUnmapInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_UnmapMemory2KHR(VkDevice device, const VkMemoryUnmapInfoKHR* pMemoryUnmapInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_UnmapMemory2KHR(VkDevice device, const VkMemoryUnmapInfoKHR* pMemoryUnmapInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_UnmapMemory2KHR(VkDevice device, const VkMemoryUnmapInfoKHR* pMemoryUnmapInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_UnmapMemory2KHR(VkDevice device, const VkMemoryUnmapInfoKHR* pMemoryUnmapInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_UnmapMemory2KHR(VkDevice device, const VkMemoryUnmapInfoKHR* pMemoryUnmapInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_UnmapMemory2KHR(VkDevice device, const VkMemoryUnmapInfoKHR* pMemoryUnmapInfo) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_UnmapMemory2KHR(VkDevice device, const VkMemoryUnmapInfoKHR* pMemoryUnmapInfo) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_CreateShadersEXT(VkDevice device, uint32_t createInfoCount, const VkShaderCreateInfoEXT* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkShaderEXT* pShaders) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_CreateShadersEXT(VkDevice device, uint32_t createInfoCount, const VkShaderCreateInfoEXT* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkShaderEXT* pShaders) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_CreateShadersEXT(VkDevice device, uint32_t createInfoCount, const VkShaderCreateInfoEXT* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkShaderEXT* pShaders) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_CreateShadersEXT(VkDevice device, uint32_t createInfoCount, const VkShaderCreateInfoEXT* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkShaderEXT* pShaders) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_CreateShadersEXT(VkDevice device, uint32_t createInfoCount, const VkShaderCreateInfoEXT* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkShaderEXT* pShaders) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_CreateShadersEXT(VkDevice device, uint32_t createInfoCount, const VkShaderCreateInfoEXT* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkShaderEXT* pShaders) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_CreateShadersEXT(VkDevice device, uint32_t createInfoCount, const VkShaderCreateInfoEXT* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkShaderEXT* pShaders) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_CreateShadersEXT(VkDevice device, uint32_t createInfoCount, const VkShaderCreateInfoEXT* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkShaderEXT* pShaders) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_DestroyShaderEXT(VkDevice device, VkShaderEXT shader, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_DestroyShaderEXT(VkDevice device, VkShaderEXT shader, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_DestroyShaderEXT(VkDevice device, VkShaderEXT shader, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_DestroyShaderEXT(VkDevice device, VkShaderEXT shader, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_DestroyShaderEXT(VkDevice device, VkShaderEXT shader, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_DestroyShaderEXT(VkDevice device, VkShaderEXT shader, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_DestroyShaderEXT(VkDevice device, VkShaderEXT shader, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_DestroyShaderEXT(VkDevice device, VkShaderEXT shader, const VkAllocationCallbacks* pAllocator) ATTR_WEAK;


  VKAPI_ATTR VkResult VKAPI_CALL anv_GetShaderBinaryDataEXT(VkDevice device, VkShaderEXT shader, size_t* pDataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx9_GetShaderBinaryDataEXT(VkDevice device, VkShaderEXT shader, size_t* pDataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx11_GetShaderBinaryDataEXT(VkDevice device, VkShaderEXT shader, size_t* pDataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx12_GetShaderBinaryDataEXT(VkDevice device, VkShaderEXT shader, size_t* pDataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL gfx125_GetShaderBinaryDataEXT(VkDevice device, VkShaderEXT shader, size_t* pDataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL doom64_GetShaderBinaryDataEXT(VkDevice device, VkShaderEXT shader, size_t* pDataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL hitman3_GetShaderBinaryDataEXT(VkDevice device, VkShaderEXT shader, size_t* pDataSize, void* pData) ATTR_WEAK;
  VKAPI_ATTR VkResult VKAPI_CALL android_GetShaderBinaryDataEXT(VkDevice device, VkShaderEXT shader, size_t* pDataSize, void* pData) ATTR_WEAK;


  VKAPI_ATTR void VKAPI_CALL anv_CmdBindShadersEXT(VkCommandBuffer commandBuffer, uint32_t stageCount, const VkShaderStageFlagBits* pStages, const VkShaderEXT* pShaders) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx9_CmdBindShadersEXT(VkCommandBuffer commandBuffer, uint32_t stageCount, const VkShaderStageFlagBits* pStages, const VkShaderEXT* pShaders) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx11_CmdBindShadersEXT(VkCommandBuffer commandBuffer, uint32_t stageCount, const VkShaderStageFlagBits* pStages, const VkShaderEXT* pShaders) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx12_CmdBindShadersEXT(VkCommandBuffer commandBuffer, uint32_t stageCount, const VkShaderStageFlagBits* pStages, const VkShaderEXT* pShaders) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL gfx125_CmdBindShadersEXT(VkCommandBuffer commandBuffer, uint32_t stageCount, const VkShaderStageFlagBits* pStages, const VkShaderEXT* pShaders) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL doom64_CmdBindShadersEXT(VkCommandBuffer commandBuffer, uint32_t stageCount, const VkShaderStageFlagBits* pStages, const VkShaderEXT* pShaders) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL hitman3_CmdBindShadersEXT(VkCommandBuffer commandBuffer, uint32_t stageCount, const VkShaderStageFlagBits* pStages, const VkShaderEXT* pShaders) ATTR_WEAK;
  VKAPI_ATTR void VKAPI_CALL android_CmdBindShadersEXT(VkCommandBuffer commandBuffer, uint32_t stageCount, const VkShaderStageFlagBits* pStages, const VkShaderEXT* pShaders) ATTR_WEAK;



#ifdef __cplusplus
}
#endif

#endif /* ANV_ENTRYPOINTS_H */
