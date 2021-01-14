# Copyright (c) 2015-2019 LunarG, Inc.

# source this file into an existing shell.

VULKAN_SDK="$(dirname "$(readlink -f "${BASH_SOURCE:-$_}" )" )/x86_64"
export VULKAN_SDK
PATH="$VULKAN_SDK/bin:$PATH"
export PATH
LD_LIBRARY_PATH="$VULKAN_SDK/lib:${LD_LIBRARY_PATH:-}"
export LD_LIBRARY_PATH
VK_LAYER_PATH="$VULKAN_SDK/etc/vulkan/explicit_layer.d"
export VK_LAYER_PATH
