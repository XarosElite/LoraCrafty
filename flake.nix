{
  description = "Arduino CLI + ESP32 Dev Shell";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};

        # Define the packages you need
        packages = with pkgs; [
          arduino-cli
          python3
          wget
          unzip
          git
          curl
          # Add additional tools here if needed
        ];
      in {
        devShells.default = pkgs.mkShell {
          name = "esp32-dev-shell";
          buildInputs = packages;

          shellHook = ''
            export PATH="$HOME/.arduino15/bin:$PATH"

            if [ ! -d "$HOME/.arduino15" ]; then
              echo "[INFO] Running 'arduino-cli config init' for first-time setup..."
              arduino-cli config init
            fi

            # Ensure ESP32 core is installed
            if ! arduino-cli core list | grep -q "esp32"; then
              echo "[INFO] Installing ESP32 core..."
              arduino-cli core update-index
              arduino-cli core install esp32:esp32
            fi

            echo "[ENV] Arduino CLI ESP32 dev shell ready."
          '';
        };
      }
    );
}

