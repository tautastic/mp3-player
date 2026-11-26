{
  description = "ESP32-C3 MP3 player";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-26.05";

  outputs = { nixpkgs, ... }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      devShells.${system}.default = pkgs.mkShell {
        nativeBuildInputs = [
          pkgs.platformio
          pkgs.gcc
          pkgs.pkg-config
        ];
        buildInputs = [
          pkgs.SDL2
        ];
      };
    };
}
