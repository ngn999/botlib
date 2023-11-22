{
  description = "A development environment for Bitcoin Core";

  inputs = {
    nixpkgs.url = "nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          config = {
            allowUnfree = false; # Bitcoin Core 是自由软件，不需要非自由依赖
            # 你可以在这里添加其他的 Nix 配置，比如优化编译参数
          };
        };
      in {
        devShell = pkgs.mkShell {
          buildInputs = with pkgs; [
            # 添加编译 Bitcoin Core 需要的最小依赖
            # 如果需要，可以在此基础上添加其他依赖项
            curl
            sqlite
            # 根据需要关闭的特性，添加相应的依赖
            # 比如，如果不需要钱包功能，你可以不包含 db4 等
          ];
          # 在这里添加你需要禁用的配置选项
          # 比如，你可以设置环境变量来禁用某些功能
          # 例如，DISABLE_WALLET, DISABLE_BENCH 等
        };
      }
    );
}
