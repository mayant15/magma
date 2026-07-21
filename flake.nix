{
  description = "The Magma Fuzzing Benchmark";
  inputs.nixpkgs.url = "flake:nixpkgs/nixos-26.05";
  outputs = { nixpkgs, ... }:
    let
      systems = ["x86_64-linux"];
      forEachSystem = nixpkgs.lib.genAttrs systems;
    in
    {
      devShells = forEachSystem ( system:
        let
          pkgs = nixpkgs.legacyPackages.${system};
        in
        {
          default = pkgs.mkShell {
            packages = [
              (pkgs.python3.withPackages (python-pkgs: with python-pkgs; [
                pandas
                numpy
              ]))
            ];
          };
        }
      );
    };
}
