clear
echo "setting up project"

read -p "Add clang build support? [y/n]:" EnableClang

mkdir subprojects

meson wrap install glfw
meson wrap install glm
meson wrap install imgui

mkdir buildgcc
mkdir buildgcc_release

CC=gcc CXX=g++ meson setup buildgcc -Dcpp_std=c++20 -Dc_std=c17 -Dc_args='' -Dcpp_args='' -Dc_link_args='-fuse-ld=mold' -Dcpp_link_args='-fuse-ld=mold' --warnlevel=1 --buildtype=debug --reconfigure --wipe

CC=gcc CXX=g++ meson setup buildgcc_release -Dcpp_std=c++20 -Dc_std=c18 -Dc_args='-Wfatal-errors' -Dcpp_args='-Wfatal-errors' -Dc_link_args='-fuse-ld=mold' -Dcpp_link_args='-fuse-ld=mold' --warnlevel=3 --buildtype=release --reconfigure --wipe

if [ "$EnableClang" == "y" ]; then
    mkdir buildclang
    mkdir buildclang_release

    CC=clang CXX=clang++ meson setup buildclang -Dcpp_std=c++20 -Dc_std=c17 -Dc_args='' -Dcpp_args='' -Dc_link_args='-fuse-ld=lld' -Dcpp_link_args='-fuse-ld=lld' --warnlevel=1 --buildtype=debug --reconfigure --wipe

    CC=clang CXX=clang++ meson setup buildclang_release -Dcpp_std=c++20 -Dc_std=c18 -Dc_args='-Wfatal-errors' -Dcpp_args='-Wfatal-errors' -Dc_link_args='-fuse-ld=lld' -Dcpp_link_args='-fuse-ld=lld' --warnlevel=3 --buildtype=release --reconfigure --wipe
fi

read -p "Build targets? [y/n]: " BuildTargets

if [ "$BuildTargets" = "y" ]; then
    meson compile -C buildgcc
    meson compile -C buildgcc_release

    if [ "$EnableClang" = "y" ]; then
        meson compile -C buildclang
        meson compile -C buildclang_release
    fi
fi