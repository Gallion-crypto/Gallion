#pragma once

#include <cstdint>

namespace CryptoNote {
	namespace parameters {

		const uint64_t CRYPTONOTE_MAX_BLOCK_NUMBER = 500000000;
		const size_t   CRYPTONOTE_MAX_BLOCK_BLOB_SIZE = 500000000;
		const size_t   CRYPTONOTE_MAX_TX_SIZE = 1000000000;
		const uint64_t CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX = 0x65ed; // addresses start with "gmt"
		const size_t   CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW = 10;
		const uint64_t CRYPTONOTE_BLOCK_FUTURE_TIME_LIMIT = 60 * 60 * 2;

		const size_t   BLOCKCHAIN_TIMESTAMP_CHECK_WINDOW = 60;

		// MONEY_SUPPLY - total number coins to be generated
		const uint64_t MONEY_SUPPLY = (uint64_t)(-1);
		const uint64_t TAIL_EMISSION_REWARD = UINT64_C(1000000000000);
		const size_t CRYPTONOTE_COIN_VERSION = 1;
		const unsigned EMISSION_SPEED_FACTOR = 22;
		static_assert(EMISSION_SPEED_FACTOR <= 8 * sizeof(uint64_t), "Bad EMISSION_SPEED_FACTOR");

		const size_t   CRYPTONOTE_REWARD_BLOCKS_WINDOW = 100;
		const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE = 1000000; //size of block (bytes) after which reward for block calculated using block size
		const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V2 = 1000000;
		const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 = 100000;
		const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_CURRENT = CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE;
		const size_t   CRYPTONOTE_COINBASE_BLOB_RESERVED_SIZE = 600;
		const size_t   CRYPTONOTE_DISPLAY_DECIMAL_POINT = 11;
		const uint64_t MINIMUM_FEE = UINT64_C(100000000);
		const uint64_t DEFAULT_DUST_THRESHOLD = MINIMUM_FEE;

		const uint64_t DIFFICULTY_TARGET = 240; // seconds
		const uint64_t EXPECTED_NUMBER_OF_BLOCKS_PER_DAY = 24 * 60 * 60 / DIFFICULTY_TARGET;
		const size_t   DIFFICULTY_WINDOW = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY; // blocks
		const size_t   DIFFICULTY_WINDOW_V2 = 17; // blocks
		const size_t   DIFFICULTY_CUT = 60;  // timestamps to cut after sorting
		const size_t   DIFFICULTY_LAG = 15;  // !!!
		static_assert(2 * DIFFICULTY_CUT <= DIFFICULTY_WINDOW - 2, "Bad DIFFICULTY_WINDOW or DIFFICULTY_CUT");

		const size_t   MAX_BLOCK_SIZE_INITIAL = 1000000;
		const uint64_t MAX_BLOCK_SIZE_GROWTH_SPEED_NUMERATOR = 100 * 1024;
		const uint64_t MAX_BLOCK_SIZE_GROWTH_SPEED_DENOMINATOR = 365 * 24 * 60 * 60 / DIFFICULTY_TARGET;

		const uint64_t CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS = 1;
		const uint64_t CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_SECONDS = DIFFICULTY_TARGET * CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS;

		const uint64_t CRYPTONOTE_MEMPOOL_TX_LIVETIME = 60 * 60 * 24;     //seconds, one day
		const uint64_t CRYPTONOTE_MEMPOOL_TX_FROM_ALT_BLOCK_LIVETIME = 60 * 60 * 24 * 7; //seconds, one week
		const uint64_t CRYPTONOTE_NUMBER_OF_PERIODS_TO_FORGET_TX_DELETED_FROM_POOL = 7;  // CRYPTONOTE_NUMBER_OF_PERIODS_TO_FORGET_TX_DELETED_FROM_POOL * CRYPTONOTE_MEMPOOL_TX_LIVETIME = time to forget tx

		const size_t   FUSION_TX_MAX_SIZE = CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_CURRENT * 30 / 100;
		const size_t   FUSION_TX_MIN_INPUT_COUNT = 12;
		const size_t   FUSION_TX_MIN_IN_OUT_COUNT_RATIO = 4;

		const uint32_t UPGRADE_HEIGHT_V2 = 60000;
		const uint32_t UPGRADE_HEIGHT_V3 = 4294967294;
		const unsigned UPGRADE_VOTING_THRESHOLD = 90;               // percent
		const uint32_t   UPGRADE_VOTING_WINDOW = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY;  // blocks
		const uint32_t   UPGRADE_WINDOW = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY;  // blocks
		static_assert(0 < UPGRADE_VOTING_THRESHOLD && UPGRADE_VOTING_THRESHOLD <= 100, "Bad UPGRADE_VOTING_THRESHOLD");
		static_assert(UPGRADE_VOTING_WINDOW > 1, "Bad UPGRADE_VOTING_WINDOW");

		const char     CRYPTONOTE_BLOCKS_FILENAME[] = "blocks.dat";
		const char     CRYPTONOTE_BLOCKINDEXES_FILENAME[] = "blockindexes.dat";
		const char     CRYPTONOTE_BLOCKSCACHE_FILENAME[] = "blockscache.dat";
		const char     CRYPTONOTE_POOLDATA_FILENAME[] = "poolstate.bin";
		const char     P2P_NET_DATA_FILENAME[] = "p2pstate.bin";
		const char     CRYPTONOTE_BLOCKCHAIN_INDICES_FILENAME[] = "blockchainindices.dat";
		const char     MINER_CONFIG_FILE_NAME[] = "miner_conf.json";
	} // parameters

	const char     CRYPTONOTE_NAME[] = "gallion";
	const char     GENESIS_COINBASE_TX_HEX[] = "010a01ff0001ffffffffff7f029b2e4c0281c0b02e7c53291a94d1d0cbff8883f8024f5142ee494ffbbd08807121015cf9e7b15a00a9a8bdda276d5e3c439b75b64cd9022bb39f412e3faef2b91f0e";

	const uint8_t  CURRENT_TRANSACTION_VERSION = 1;
	const uint8_t  BLOCK_MAJOR_VERSION_1 = 1;
	const uint8_t  BLOCK_MAJOR_VERSION_2 = 2;
	const uint8_t  BLOCK_MAJOR_VERSION_3 = 3;
	const uint8_t  BLOCK_MINOR_VERSION_0 = 0;
	const uint8_t  BLOCK_MINOR_VERSION_1 = 1;

	const size_t   BLOCKS_IDS_SYNCHRONIZING_DEFAULT_COUNT = 10000;  //by default, blocks ids count in synchronizing
	const size_t   BLOCKS_SYNCHRONIZING_DEFAULT_COUNT = 200;    //by default, blocks count in blocks downloading
	const size_t   COMMAND_RPC_GET_BLOCKS_FAST_MAX_COUNT = 1000;

	const int      P2P_DEFAULT_PORT = 6012;
	const int      RPC_DEFAULT_PORT = 1119;

	const size_t   P2P_LOCAL_WHITE_PEERLIST_LIMIT = 5050;
	const size_t   P2P_LOCAL_GRAY_PEERLIST_LIMIT = 5000;

	const size_t   P2P_CONNECTION_MAX_WRITE_BUFFER_SIZE = 64 * 1024 * 1024; // 64 MB
	const uint32_t P2P_DEFAULT_CONNECTIONS_COUNT = 8;
	const size_t   P2P_DEFAULT_WHITELIST_CONNECTIONS_PERCENT = 70;
	const uint32_t P2P_DEFAULT_HANDSHAKE_INTERVAL = 60;            // seconds
	const uint32_t P2P_DEFAULT_PACKET_MAX_SIZE = 50000000;      // 50000000 bytes maximum packet size
	const uint32_t P2P_DEFAULT_PEERS_IN_HANDSHAKE = 250;
	const uint32_t P2P_DEFAULT_CONNECTION_TIMEOUT = 5000;          // 5 seconds
	const uint32_t P2P_DEFAULT_PING_CONNECTION_TIMEOUT = 2000;          // 2 seconds
	const uint64_t P2P_DEFAULT_INVOKE_TIMEOUT = 60 * 2 * 1000; // 2 minutes
	const size_t   P2P_DEFAULT_HANDSHAKE_INVOKE_TIMEOUT = 5000;          // 5 seconds
	const char     P2P_STAT_TRUSTED_PUB_KEY[] = "8f80f9a5a434a9f1510d13336228debfee9c918ce505efe225d8c94d045fa115";

	const char* const SEED_NODES[] = {
		"gallion.ddns.net:6012",
		"gallion.ddns.net:6013"
	};

	struct CheckpointData {
		uint32_t height;
		const char* blockId;
	};

	const std::initializer_list<CheckpointData> CHECKPOINTS = {
		{ 2000,	"915357c2512935fc334d19475c46dbe876c420c18f05bb4cf771fc2b3ca34d6c" },
		{ 4000,	"f4ec92a77f6455e0bb29d84f4b5eaf04d2339d776451e23c3da0cee2df595de7" },
		{ 10000, "a3dec8d7cd7abf27e0cb1e039bd024f3d18de4171eb73eb0a066ce5fd7760219" },
		{ 15000, "0b5ecaf40d914fa6e9a684cbe7b051aad43a5837d8851ef07ad765274833bcaa" },
		{ 20000, "baee36ab45dc22b51c014cc68c13dcea58ea8af241e713a6c5b66c62b27103ae" },
		{ 25000, "3e44ac3977a88f17206719a5a989e852c7d153b1f9d02514cd7134f3b7cd7db3" },
		{ 30000, "05db337e1bbcdef3a2524e914e81a7c8be37f98f462a3d70b834bd6a0aa5b8c5" },
		{ 35000, "e15adf8c0e02e15168b0f4c26cf28b26c4f26115ebd4d13ec54836a414623761" },
		{ 40000, "9dc58d62039b75f16ce06fd85caaa3412f2b800658e0b5b4c32b8fd2c08ffe56" },
		{ 60000, "9f8144d2321e08c97b3da82d8259803d822f76be0010db6a887df67c10640fdf" }
	};

} // CryptoNote

#define ALLOW_DEBUG_COMMANDS


