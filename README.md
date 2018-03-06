C'est le code de référence pour le protocole crypto-monnaie [CryptoNote] (https://cryptonote.org).

* Lancez votre propre devise CryptoNote: [CryptoNote Starter] (https://cryptonotestarter.org/)
* Implémentation de référence CryptoNote: [CryptoNoteCoin] (https://cryptonote-coin.org)
* Forum de discussion et support: [Forum CryptoNote] (https://forum.cryptonote.org)

## CryptoNote comment-faire

### Preparation

1. Créez un compte sur [GitHub.com] (github.com)
2. Branch [référentiel CryptoNote] (https://github.com/cryptonotefoundation/cryptonote)
3. Achetez un ou deux serveurs dédiés basés sur Ubuntu (au moins 2 Go de RAM) pour les noeuds d'amorçage.


### Premier pas. Donnez un nom à votre pièce

** Un bon nom doit être unique. ** Vérifiez l'unicité avec [google] (http://google.com) et [Map of Coins] (mapofcoins.com) ou tout autre service similaire.

Le nom doit être spécifié deux fois:

**1. dans le fichier src/CryptoNoteConfig.h** - `CRYPTONOTE_NAME` constant

Exemple: 
```
const char CRYPTONOTE_NAME[] = "gallion";
```

**2. dans src/CMakeList.txt file** - set_property(TARGET daemon PROPERTY OUTPUT_NAME "YOURCOINNAME**d**")

Exemple: 
```
set_property(TARGET daemon PROPERTY OUTPUT_NAME "gallion")
```

** Note: ** Vous devez également modifier le nom du référentiel.


### Deuxième étape. Logique d'émission

**1. Masse monétaire totale ** (src/CryptoNoteConfig.h)

Quantité totale de pièces à émettre. La plupart des pièces à base de CryptoNote utilisent`(uint64_t)(-1)` (est égal à18446744073709551616). Vous pouvez définir un nombre explicitement (par exemple `UINT64_C(858986905600000000)`).

Exemple:
```
const uint64_t MONEY_SUPPLY = (uint64_t)(-1);
```

** 2. Courbe d'émission ** (src/CryptoNoteConfig.h)

Par défaut, CryptoNote fournit une formule d'émission avec une légère diminution de la récompense de bloc pour chaque bloc. Ceci est différent de Bitcoin où la récompense de bloc diminue de moitié tous les 4 ans.

La constante 'EMISSION_SPEED_FACTOR` définit la pente de la courbe d'émission. Ce paramètre est requis pour calculer la récompense de bloc.

Exemple:
```
const unsigned EMISSION_SPEED_FACTOR = 18;
```

** 3. Difficulté cible ** (src / CryptoNoteConfig.h)

La cible de difficulté est une période idéale entre les blocs. Dans le cas où un temps moyen entre blocs devient inférieur à la difficulté, la difficulté augmente. La cible de difficulté est mesurée en secondes.

La cible de difficulté influence directement plusieurs aspects du comportement de la pièce:

- vitesse de confirmation de la transaction: plus la durée entre les blocs est longue, plus la confirmation de la transaction est lente
- vitesse d'émission: plus le temps entre les blocs est long, plus le processus d'émission est lent
- taux d'orphelin: les chaînes avec des blocs très rapides ont un plus grand taux d'orphelin

Pour la plupart des pièces, la difficulté est de 60 ou 120 secondes.

Exemple:
```
const uint64_t DIFFICULTY_TARGET = 120;
```

**4. Formule de récompense de bloc**

Dans le cas où vous n'êtes pas satisfait de l'implémentation par défaut de la logique de récompense de bloc de CryptoNote, vous pouvez également la modifier. L'implémentation est dans`src/CryptoNoteCore/Currency.cpp`:
```
bool Currency::getBlockReward(size_t medianSize, size_t currentBlockSize, uint64_t alreadyGeneratedCoins, uint64_t fee, uint64_t& reward, int64_t& emissionChange) const
```

Cette fonction a deux parties:

- calcul de la récompense de base du bloc: `uint64_t baseReward = (m_moneySupply - alreadyGeneratedCoins) >> m_emissionSpeedFactor;`
- calcul de la pénalité de gros bloc: c'est ainsi que CryptoNote protège la chaîne de blocs contre les attaques par inondation de transaction et préserve les opportunités de croissance organique du réseau en même temps.

Seule la première partie de cette fonction est directement liée à la logique d'émission. Vous pouvez le changer comme vous le souhaitez. Voir MonetaVerde et DuckNote comme exemples où cette fonction est modifiée.


### Troisième étape. La mise en réseau

**1. Les ports par défaut pour les réseaux P2P et RPC** (src/CryptoNoteConfig.h)

Le port P2P est utilisé par les daemons pour se parler via le protocole P2P.
Le port RPC est utilisé par le portefeuille et d'autres programmes pour parler au daemons.

Il est préférable de choisir les ports qui ne sont pas utilisés par d'autres logiciels ou pièces de monnaie. Voir les listes de ports TCP connues:

* http://www.speedguide.net/ports.php
* http://www.networksorcery.com/enp/protocol/ip/ports00000.htm
* http://keir.net/portlist.html

Exemple:
```
const int P2P_DEFAULT_PORT = 17236;
const int RPC_DEFAULT_PORT = 18236;
```


**2.  Identifiant de réseau** (src/P2p/P2pNetworks.h)

Cet identifiant est utilisé dans les paquets réseau afin de ne pas mélanger deux réseaux cryptocoin différents. Changez tous les octets en valeurs aléatoires pour votre réseau:
```
const static boost::uuids::uuid CRYPTONOTE_NETWORK = { { 0xA1, 0x1A, 0xA1, 0x1A, 0xA1, 0x0A, 0xA1, 0x0A, 0xA0, 0x1A, 0xA0, 0x1A, 0xA0, 0x1A, 0xA1, 0x1A } };
```


**3. Noeud de départ** (src/CryptoNoteConfig.h)

Ajoutez des adresses IP de vos noeuds de départ.

Exemple:
```
const std::initializer_list<const char*> SEED_NODES = {
  "111.11.11.11:17236",
  "222.22.22.22:17236",
};
```


### Quatrième étape. Frais de transaction et paramètres associés

**1. Frais de transaction minimum** (src/CryptoNoteConfig.h)

Frais minimum zéro peut conduire à une inondation de transaction. Les transactions moins chères que les frais de transaction minimum ne seraient pas acceptées par les daemons. La valeur 100000 pour `MINIMUM_FEE` est généralement suffisante.

Exemple:
```
const uint64_t MINIMUM_FEE = 100000;
```


**2. Taille de bloc sans pénalité** (src/CryptoNoteConfig.h)

CryptoNote protège la chaîne contre l'inondation de tx en réduisant la récompense de bloc pour les blocs plus grands que la taille de bloc médiane. Cependant, cette règle s'applique aux blocs plus grands que les octets `CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE` bytes.

Exemple:
```
const size_t CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE = 20000;
```


### Cinquième étape. Adresse préfixe

Vous pouvez choisir une lettre (dans certains cas plusieurs lettres) toutes les adresses publiques de la pièce commenceront par. Il est défini par la constante `CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX`. Puisque les règles pour les préfixes d'adresse sont non triviales, vous pouvez utiliser l'outil [générateur de préfixes] (https://cryptonotestarter.org/tools.html).

Example:
```
const uint64_t CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX = 0xe9; // les adresses commencent par "f"
```


### Sixième étape. Bloc de la Genèse

**1. Construire les binaires avec genesis tx hex vide** (src/CryptoNoteConfig.h)

Vous devez laisser `const char GENESIS_COINBASE_TX_HEX []` vide et compiler les binaires sans lui.

Exemple:
```
const char GENESIS_COINBASE_TX_HEX[] = "";
```


** 2. Démarrez le démon pour imprimer le bloc de genèse **

Exécutez votre daemon avec l'argument `--print-genesis-tx`. Il imprimera le hachage de transaction coinbase du bloc genesis.

Exemple:
```
gallion --print-genesis-tx
```

**3. Copiez le hachage de transaction imprimé** (src/CryptoNoteConfig.h)

Copiez le hachage tx qui a été imprimé par le daemon dans `GENESIS_COINBASE_TX_HEX` in `src/CryptoNoteConfig.h`

Example:
```
const char GENESIS_COINBASE_TX_HEX[] = "013c01ff0001ffff...785a33d9ebdba68b0";
```


** 4. Recompilez les binaires **

Recompilez tout encore. Votre code de pièce est prêt maintenant. Faites une annonce pour les utilisateurs potentiels et amusez-vous!

## Construire CryptoNote 

### On *nix

Dépendances: GCC 4.7.3 ou ultérieur, CMake 2.8.6 ou ultérieur et Boost 1.55.

Vous pouvez les télécharger depuis:
* http://gcc.gnu.org/
* http://www.cmake.org/
* http://www.boost.org/
* Alternativement, il peut être possible de les installer en utilisant un gestionnaire de paquets.

Pour construire, placez-vous dans un répertoire où se trouve ce fichier et lancez `make`. Les exécutables résultants peuvent être trouvés dans `build/release/src`.

**Advanced options:**

* 
* Parallel build: lance `make -j<number of threads>` au lieu de `make`.
* Debug build: lance `make build-debug`.
* Suite de tests: exécutez `make test-release` pour exécuter des tests en plus de la construction. L'exécution de `make test-debug` fera de même avec la version de débogage.
* Construire avec Clang: il peut être possible d'utiliser Clang au lieu de GCC, mais cela peut ne pas fonctionner partout. Pour compiler, lancez `export CC=clang CXX=clang++` avant d'exécuter `make`.

### Sur Windows
Dépendances: MSVC 2013 ou ultérieur, CMake 2.8.6 ou ultérieur et Boost 1.55. Vous pouvez les télécharger depuis:

* http://www.microsoft.com/
* http://www.cmake.org/
* http://www.boost.org/

Pour construire, passez à un répertoire où se trouve ce fichier et exécutez les commandes: 
```
mkdir build
cd build
cmake -G "Visual Studio 12 Win64" ..
```

Et puis faites Build.
Bonne chance!# Gallion
