Gallion est une crypto-monnaie d'origine française, tout comme Bitcoin mais plus anonyme et centré sur la vie privée avec une blockchain opaque et plus résistante à l'analyse. C'est l'argent électronique des gens, pas relié au gouvernement ou aux fonctionnaires.

## Construire Gallion

### On * nix

Dépendances: GCC 4.7.3 ou ultérieur, CMake 2.8.6 ou ultérieur et Boost 1.55.

Vous pouvez les télécharger depuis:

* http://gcc.gnu.org/
* http://www.cmake.org/
* http://www.boost.org/
* Alternativement, il peut être possible de les installer en utilisant un gestionnaire de paquets.

Pour construire, placez-vous dans un répertoire où se trouve ce fichier et lancez `make`. Les exécutables résultants peuvent être trouvés dans `build/release/src`.

**Options avancées:**

* Parallel build: lance `make -j<number of threads>` au lieu de `make`.
* Debug build: lance `make build-debug`.
* Suite de tests: exécutez `make test-release` pour exécuter des tests en plus de la construction. L'exécution de `make test-debug` fera de même avec la version de débogage.
* Construire avec Clang: il peut être possible d'utiliser Clang au lieu de GCC, mais cela peut ne pas fonctionner partout. Pour compiler, lancez `export CC=clang CXX=clang++` avant d'exécuter `make`.

### Sur Windows
Dépendances: MSVC 2013 ou ultérieur, CMake 2.8.6 ou ultérieur et Boost 1.55. Vous pouvez les télécharger depuis:

* http://www.microsoft.com/
* http://www.cmake.org/
* http://www.boost.org/

Pour construire, passez à un répertoire où se trouve ce fichier et exécutez les commandes theas:
```
mkdir build
cd build
cmake -G "Visual Studio 12 Win64" ..
```

Et puis faites Build.
Bonne chance!

### Construire pour Android sous Linux

Configurer la chaîne d'outils 32 bits
Télécharger et extraire le SDK Android et NDK
```
android-ndk-r15c/build/tools/make_standalone_toolchain.py --api 21 --stl=libc++ --arch arm --install-dir /opt/android/tool32
```

Téléchargez et installez la source Boost 1.65.1
```
wget https://sourceforge.net/projects/boost/files/boost/1.65.1/boost_1_65_1.tar.bz2/download -O boost_1_65_1.tar.bz2
tar xjf boost_1_65_1.tar.bz2
cd boost_1_65_1
./bootstrap.sh
```
appliquer le correctif depuis external/boost1_65_1/libs/filesystem/src

Construire Boost avec la chaîne d'outils 32 bits
`` `
export PATH=/opt/android/tool32/arm-linux-androideabi/bin:/opt/android/tool32/bin:$PATH
./b2 abi=aapcs architecture=arm binary-format=elf address-model=32 link=static runtime-link=static --with-chrono --with-date_time --with-filesystem --with-program_options --with-regex --with-serialization --with-system --with-thread --with-context --with-coroutine --with-atomic --build-dir=android32 --stagedir=android32 toolset=clang threading=multi threadapi=pthread target-os=android --reconfigure stage
```

Construire Gallion pour 32 bits Android
```
mkdir -p build/release.android32
cd build/release.android32
CC=clang CXX=clang++ cmake -D BUILD_TESTS=OFF -D ARCH="armv7-a" -ldl -D STATIC=ON -D BUILD_64=OFF -D CMAKE_BUILD_TYPE=release -D ANDROID=true -D BUILD_TAG="android" -D BOOST_ROOT=/opt/android/boost_1_65_1 -D BOOST_LIBRARYDIR=/opt/android/boost_1_65_1/android32/lib -D CMAKE_POSITION_INDEPENDENT_CODE:BOOL=true -D BOOST_IGNORE_SYSTEM_PATHS_DEFAULT=ON ../..
make SimpleWallet
```
