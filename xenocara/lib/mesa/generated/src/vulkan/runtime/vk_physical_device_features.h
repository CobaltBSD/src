
/* Copyright © 2021 Intel Corporation
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

/* This file generated from vk_physical_device_features.py, don't edit directly. */
#ifndef VK_FEATURES_H
#define VK_FEATURES_H

#ifdef __cplusplus
extern "C" {
#endif

struct vk_features {
   bool robustBufferAccess;
   bool fullDrawIndexUint32;
   bool imageCubeArray;
   bool independentBlend;
   bool geometryShader;
   bool tessellationShader;
   bool sampleRateShading;
   bool dualSrcBlend;
   bool logicOp;
   bool multiDrawIndirect;
   bool drawIndirectFirstInstance;
   bool depthClamp;
   bool depthBiasClamp;
   bool fillModeNonSolid;
   bool depthBounds;
   bool wideLines;
   bool largePoints;
   bool alphaToOne;
   bool multiViewport;
   bool samplerAnisotropy;
   bool textureCompressionETC2;
   bool textureCompressionASTC_LDR;
   bool textureCompressionBC;
   bool occlusionQueryPrecise;
   bool pipelineStatisticsQuery;
   bool vertexPipelineStoresAndAtomics;
   bool fragmentStoresAndAtomics;
   bool shaderTessellationAndGeometryPointSize;
   bool shaderImageGatherExtended;
   bool shaderStorageImageExtendedFormats;
   bool shaderStorageImageMultisample;
   bool shaderStorageImageReadWithoutFormat;
   bool shaderStorageImageWriteWithoutFormat;
   bool shaderUniformBufferArrayDynamicIndexing;
   bool shaderSampledImageArrayDynamicIndexing;
   bool shaderStorageBufferArrayDynamicIndexing;
   bool shaderStorageImageArrayDynamicIndexing;
   bool shaderClipDistance;
   bool shaderCullDistance;
   bool shaderFloat64;
   bool shaderInt64;
   bool shaderInt16;
   bool shaderResourceResidency;
   bool shaderResourceMinLod;
   bool sparseBinding;
   bool sparseResidencyBuffer;
   bool sparseResidencyImage2D;
   bool sparseResidencyImage3D;
   bool sparseResidency2Samples;
   bool sparseResidency4Samples;
   bool sparseResidency8Samples;
   bool sparseResidency16Samples;
   bool sparseResidencyAliased;
   bool variableMultisampleRate;
   bool inheritedQueries;
   bool deviceGeneratedCommands;
   bool privateData;
   bool variablePointersStorageBuffer;
   bool variablePointers;
   bool multiview;
   bool multiviewGeometryShader;
   bool multiviewTessellationShader;
   bool presentId;
   bool presentWait;
   bool storageBuffer16BitAccess;
   bool uniformAndStorageBuffer16BitAccess;
   bool storagePushConstant16;
   bool storageInputOutput16;
   bool shaderSubgroupExtendedTypes;
   bool samplerYcbcrConversion;
   bool protectedMemory;
   bool advancedBlendCoherentOperations;
   bool multiDraw;
   bool inlineUniformBlock;
   bool descriptorBindingInlineUniformBlockUpdateAfterBind;
   bool maintenance4;
   bool shaderDrawParameters;
   bool shaderFloat16;
   bool shaderInt8;
   bool hostQueryReset;
   bool globalPriorityQuery;
   bool deviceMemoryReport;
   bool shaderInputAttachmentArrayDynamicIndexing;
   bool shaderUniformTexelBufferArrayDynamicIndexing;
   bool shaderStorageTexelBufferArrayDynamicIndexing;
   bool shaderUniformBufferArrayNonUniformIndexing;
   bool shaderSampledImageArrayNonUniformIndexing;
   bool shaderStorageBufferArrayNonUniformIndexing;
   bool shaderStorageImageArrayNonUniformIndexing;
   bool shaderInputAttachmentArrayNonUniformIndexing;
   bool shaderUniformTexelBufferArrayNonUniformIndexing;
   bool shaderStorageTexelBufferArrayNonUniformIndexing;
   bool descriptorBindingUniformBufferUpdateAfterBind;
   bool descriptorBindingSampledImageUpdateAfterBind;
   bool descriptorBindingStorageImageUpdateAfterBind;
   bool descriptorBindingStorageBufferUpdateAfterBind;
   bool descriptorBindingUniformTexelBufferUpdateAfterBind;
   bool descriptorBindingStorageTexelBufferUpdateAfterBind;
   bool descriptorBindingUpdateUnusedWhilePending;
   bool descriptorBindingPartiallyBound;
   bool descriptorBindingVariableDescriptorCount;
   bool runtimeDescriptorArray;
   bool timelineSemaphore;
   bool storageBuffer8BitAccess;
   bool uniformAndStorageBuffer8BitAccess;
   bool storagePushConstant8;
   bool conditionalRendering;
   bool inheritedConditionalRendering;
   bool vulkanMemoryModel;
   bool vulkanMemoryModelDeviceScope;
   bool vulkanMemoryModelAvailabilityVisibilityChains;
   bool shaderBufferInt64Atomics;
   bool shaderSharedInt64Atomics;
   bool shaderBufferFloat32Atomics;
   bool shaderBufferFloat32AtomicAdd;
   bool shaderBufferFloat64Atomics;
   bool shaderBufferFloat64AtomicAdd;
   bool shaderSharedFloat32Atomics;
   bool shaderSharedFloat32AtomicAdd;
   bool shaderSharedFloat64Atomics;
   bool shaderSharedFloat64AtomicAdd;
   bool shaderImageFloat32Atomics;
   bool shaderImageFloat32AtomicAdd;
   bool sparseImageFloat32Atomics;
   bool sparseImageFloat32AtomicAdd;
   bool shaderBufferFloat16Atomics;
   bool shaderBufferFloat16AtomicAdd;
   bool shaderBufferFloat16AtomicMinMax;
   bool shaderBufferFloat32AtomicMinMax;
   bool shaderBufferFloat64AtomicMinMax;
   bool shaderSharedFloat16Atomics;
   bool shaderSharedFloat16AtomicAdd;
   bool shaderSharedFloat16AtomicMinMax;
   bool shaderSharedFloat32AtomicMinMax;
   bool shaderSharedFloat64AtomicMinMax;
   bool shaderImageFloat32AtomicMinMax;
   bool sparseImageFloat32AtomicMinMax;
   bool vertexAttributeInstanceRateDivisor;
   bool vertexAttributeInstanceRateZeroDivisor;
   bool decodeModeSharedExponent;
   bool transformFeedback;
   bool geometryStreams;
   bool representativeFragmentTest;
   bool exclusiveScissor;
   bool cornerSampledImage;
   bool computeDerivativeGroupQuads;
   bool computeDerivativeGroupLinear;
   bool imageFootprint;
   bool dedicatedAllocationImageAliasing;
   bool indirectCopy;
   bool memoryDecompression;
   bool shadingRateImage;
   bool shadingRateCoarseSampleOrder;
   bool invocationMask;
   bool taskShaderNV;
   bool meshShaderNV;
   bool taskShader;
   bool meshShader;
   bool multiviewMeshShader;
   bool primitiveFragmentShadingRateMeshShader;
   bool meshShaderQueries;
   bool accelerationStructure;
   bool accelerationStructureCaptureReplay;
   bool accelerationStructureIndirectBuild;
   bool accelerationStructureHostCommands;
   bool descriptorBindingAccelerationStructureUpdateAfterBind;
   bool rayTracingPipeline;
   bool rayTracingPipelineShaderGroupHandleCaptureReplay;
   bool rayTracingPipelineShaderGroupHandleCaptureReplayMixed;
   bool rayTracingPipelineTraceRaysIndirect;
   bool rayTraversalPrimitiveCulling;
   bool rayQuery;
   bool rayTracingMaintenance1;
   bool rayTracingPipelineTraceRaysIndirect2;
   bool fragmentDensityMap;
   bool fragmentDensityMapDynamic;
   bool fragmentDensityMapNonSubsampledImages;
   bool fragmentDensityMapDeferred;
   bool fragmentDensityMapOffset;
   bool scalarBlockLayout;
   bool uniformBufferStandardLayout;
   bool depthClipEnable;
   bool memoryPriority;
   bool pageableDeviceLocalMemory;
   bool bufferDeviceAddress;
   bool bufferDeviceAddressCaptureReplay;
   bool bufferDeviceAddressMultiDevice;
   bool bufferDeviceAddressCaptureReplayEXT;
   bool imagelessFramebuffer;
   bool textureCompressionASTC_HDR;
   bool cooperativeMatrix;
   bool cooperativeMatrixRobustBufferAccess;
   bool ycbcrImageArrays;
   bool presentBarrier;
   bool performanceCounterQueryPools;
   bool performanceCounterMultipleQueryPools;
   bool coverageReductionMode;
   bool shaderIntegerFunctions2;
   bool shaderSubgroupClock;
   bool shaderDeviceClock;
   bool indexTypeUint8;
   bool shaderSMBuiltins;
   bool fragmentShaderSampleInterlock;
   bool fragmentShaderPixelInterlock;
   bool fragmentShaderShadingRateInterlock;
   bool separateDepthStencilLayouts;
   bool primitiveTopologyListRestart;
   bool primitiveTopologyPatchListRestart;
   bool pipelineExecutableInfo;
   bool shaderDemoteToHelperInvocation;
   bool texelBufferAlignment;
   bool subgroupSizeControl;
   bool computeFullSubgroups;
   bool rectangularLines;
   bool bresenhamLines;
   bool smoothLines;
   bool stippledRectangularLines;
   bool stippledBresenhamLines;
   bool stippledSmoothLines;
   bool pipelineCreationCacheControl;
   bool samplerMirrorClampToEdge;
   bool drawIndirectCount;
   bool descriptorIndexing;
   bool samplerFilterMinmax;
   bool shaderOutputViewportIndex;
   bool shaderOutputLayer;
   bool subgroupBroadcastDynamicId;
   bool robustImageAccess;
   bool shaderTerminateInvocation;
   bool synchronization2;
   bool shaderZeroInitializeWorkgroupMemory;
   bool dynamicRendering;
   bool shaderIntegerDotProduct;
   bool deviceCoherentMemory;
   bool customBorderColors;
   bool customBorderColorWithoutFormat;
   bool borderColorSwizzle;
   bool borderColorSwizzleFromImage;
   bool extendedDynamicState;
   bool extendedDynamicState2;
   bool extendedDynamicState2LogicOp;
   bool extendedDynamicState2PatchControlPoints;
   bool extendedDynamicState3TessellationDomainOrigin;
   bool extendedDynamicState3DepthClampEnable;
   bool extendedDynamicState3PolygonMode;
   bool extendedDynamicState3RasterizationSamples;
   bool extendedDynamicState3SampleMask;
   bool extendedDynamicState3AlphaToCoverageEnable;
   bool extendedDynamicState3AlphaToOneEnable;
   bool extendedDynamicState3LogicOpEnable;
   bool extendedDynamicState3ColorBlendEnable;
   bool extendedDynamicState3ColorBlendEquation;
   bool extendedDynamicState3ColorWriteMask;
   bool extendedDynamicState3RasterizationStream;
   bool extendedDynamicState3ConservativeRasterizationMode;
   bool extendedDynamicState3ExtraPrimitiveOverestimationSize;
   bool extendedDynamicState3DepthClipEnable;
   bool extendedDynamicState3SampleLocationsEnable;
   bool extendedDynamicState3ColorBlendAdvanced;
   bool extendedDynamicState3ProvokingVertexMode;
   bool extendedDynamicState3LineRasterizationMode;
   bool extendedDynamicState3LineStippleEnable;
   bool extendedDynamicState3DepthClipNegativeOneToOne;
   bool extendedDynamicState3ViewportWScalingEnable;
   bool extendedDynamicState3ViewportSwizzle;
   bool extendedDynamicState3CoverageToColorEnable;
   bool extendedDynamicState3CoverageToColorLocation;
   bool extendedDynamicState3CoverageModulationMode;
   bool extendedDynamicState3CoverageModulationTableEnable;
   bool extendedDynamicState3CoverageModulationTable;
   bool extendedDynamicState3CoverageReductionMode;
   bool extendedDynamicState3RepresentativeFragmentTestEnable;
   bool extendedDynamicState3ShadingRateImageEnable;
   bool diagnosticsConfig;
   bool shaderSubgroupUniformControlFlow;
   bool robustBufferAccess2;
   bool robustImageAccess2;
   bool nullDescriptor;
   bool workgroupMemoryExplicitLayout;
   bool workgroupMemoryExplicitLayoutScalarBlockLayout;
   bool workgroupMemoryExplicitLayout8BitAccess;
   bool workgroupMemoryExplicitLayout16BitAccess;
   bool formatA4R4G4B4;
   bool formatA4B4G4R4;
   bool subpassShading;
   bool clustercullingShader;
   bool multiviewClusterCullingShader;
   bool shaderImageInt64Atomics;
   bool sparseImageInt64Atomics;
   bool pipelineFragmentShadingRate;
   bool primitiveFragmentShadingRate;
   bool attachmentFragmentShadingRate;
   bool fragmentShadingRateEnums;
   bool supersampleFragmentShadingRates;
   bool noInvocationFragmentShadingRates;
   bool image2DViewOf3D;
   bool sampler2DViewOf3D;
   bool imageSlicedViewOf3D;
   bool mutableDescriptorType;
   bool depthClipControl;
   bool vertexInputDynamicState;
   bool externalMemoryRDMA;
   bool colorWriteEnable;
   bool primitivesGeneratedQuery;
   bool primitivesGeneratedQueryWithRasterizerDiscard;
   bool primitivesGeneratedQueryWithNonZeroStreams;
   bool legacyDithering;
   bool multisampledRenderToSingleSampled;
   bool pipelineProtectedAccess;
   bool inheritedViewportScissor2D;
   bool ycbcr2plane444Formats;
   bool provokingVertexLast;
   bool transformFeedbackPreservesProvokingVertex;
   bool descriptorBuffer;
   bool descriptorBufferCaptureReplay;
   bool descriptorBufferImageLayoutIgnored;
   bool descriptorBufferPushDescriptors;
   bool fragmentShaderBarycentric;
   bool rayTracingMotionBlur;
   bool rayTracingMotionBlurPipelineTraceRaysIndirect;
   bool formatRgba10x6WithoutYCbCrSampler;
   bool minLod;
   bool rasterizationOrderColorAttachmentAccess;
   bool rasterizationOrderDepthAttachmentAccess;
   bool rasterizationOrderStencilAttachmentAccess;
   bool linearColorAttachment;
   bool graphicsPipelineLibrary;
   bool descriptorSetHostMapping;
   bool shaderModuleIdentifier;
   bool imageCompressionControl;
   bool imageCompressionControlSwapchain;
   bool subpassMergeFeedback;
   bool micromap;
   bool micromapCaptureReplay;
   bool micromapHostCommands;
   bool pipelinePropertiesIdentifier;
   bool shaderEarlyAndLateFragmentTests;
   bool nonSeamlessCubeMap;
   bool pipelineRobustness;
   bool textureSampleWeighted;
   bool textureBoxFilter;
   bool textureBlockMatch;
   bool tileProperties;
   bool amigoProfiling;
   bool attachmentFeedbackLoopLayout;
   bool depthClampZeroOne;
   bool reportAddressBinding;
   bool opticalFlow;
   bool deviceFault;
   bool deviceFaultVendorBinary;
   bool pipelineLibraryGroupHandles;
   bool shaderCoreBuiltins;
   bool swapchainMaintenance1;
   bool rayTracingInvocationReorder;
   bool multiviewPerViewViewports;
   bool multiviewPerViewRenderAreas;
   bool shaderObject;
   bool shaderTileImageColorReadAccess;
   bool shaderTileImageDepthReadAccess;
   bool shaderTileImageStencilReadAccess;
};

void
vk_set_physical_device_features_1_0(struct vk_features *all_features,
                                    const VkPhysicalDeviceFeatures *pFeatures);

void
vk_set_physical_device_features(struct vk_features *all_features,
                                const VkPhysicalDeviceFeatures2 *pFeatures);

void
vk_get_physical_device_features(VkPhysicalDeviceFeatures2 *pFeatures,
                                const struct vk_features *all_features);

#ifdef __cplusplus
}
#endif

#endif
