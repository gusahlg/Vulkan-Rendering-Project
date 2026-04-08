{
  description = "Vulkan Rendering Project development shell";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            cmake
            ninja
            pkg-config
            gcc
            glfw
            glm
            shaderc
            vulkan-headers
            vulkan-loader
            vulkan-tools
            vulkan-validation-layers
            libxkbcommon
            wayland
            xorg.libX11
            xorg.libXcursor
            xorg.libXi
            xorg.libXinerama
            xorg.libXrandr
            xorg.libXxf86vm
          ];

          LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [
            pkgs.glfw
            pkgs.vulkan-loader
            pkgs.libxkbcommon
            pkgs.wayland
            pkgs.xorg.libX11
            pkgs.xorg.libXcursor
            pkgs.xorg.libXi
            pkgs.xorg.libXinerama
            pkgs.xorg.libXrandr
            pkgs.xorg.libXxf86vm
          ];

          VK_LAYER_PATH = "${pkgs.vulkan-validation-layers}/share/vulkan/explicit_layer.d";
        };
      });
}
