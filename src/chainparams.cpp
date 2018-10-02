// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "util.h"
#include "utilstrencodings.h"
#include "arith_uint256.h"
#include "random.h"
#include <assert.h>
#include "aligned_malloc.h"

#include <boost/assign/list_of.hpp>

using namespace std;

#include "chainparamsseeds.h"

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 819678;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.powLimit = uint256S("0fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 3 * 60; // one hour
        consensus.nPowTargetSpacing = 3 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        /** 
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xf9;
        pchMessageStart[1] = 0xbc;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xd9;
        vAlertPubKey = ParseHex("046adee5560fe6ca6fee47f8c03b67f9927e077e4aec63723a99de074574b024b1ad295dc565cdb6938b0efb4c140152d33c951bbfd7071a17c089997313c29ba5");
        nDefaultPort = 1989;
        nMinerThreads = 0;
        nMaxTipAge = 24 * 60 * 60;
        nPruneAfterHeight = 100000;

        /**
         * Build the genesis block. Note that the output of its generation
         * transaction cannot be spent since it did not originally exist in the
         * database.
         *
         * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
         *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
         *   vMerkleTree: 4a5e1e
         */
        const char* pszTimestamp = "FAUCETIUM TEAM";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("046adee5560fe6ca6fee47f8c03b67f9927e077e4aec63723a99de074574b024b1ad295dc565cdb6938b0efb4c140152d33c951bbfd7071a17c089997313c29ba5") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock.SetNull();
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1538397469;
        genesis.nBits    = 0x21000FFF;
        genesis.nNonce   = 1989891989;
        genesis.nStartLocation = 399;
        genesis.nFinalCalculation = 865734594;
        if(genesis.GetHash() != uint256S("00afc7c2b815a7424edcafbee0d6645c0cf1104db59f2547e2491c6f8112b84e") ){
            arith_uint256 hashTarget = arith_uint256().SetCompact(genesis.nBits);
            uint256 thash;
            char *scratchpad;
            scratchpad = (char*)aligned_malloc(1<<30);
            while(true){
                int collisions=0;
								int tmpflag=0;
								thash = genesis.FindBestPatternHash(collisions,scratchpad,8,&tmpflag);
								LogPrintf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(),
                hashTarget.ToString().c_str());
                if (UintToArith256(thash) <= hashTarget)
                    break;
                genesis.nNonce=genesis.nNonce+10000;
                if (genesis.nNonce == 0){
                    LogPrintf("NONCE WRAPPED, incrementing time\n");
                    ++genesis.nTime;
                }
            }
            aligned_free(scratchpad);
            LogPrintf("block.nTime = %u \n", genesis.nTime);
            LogPrintf("block.nNonce = %u \n", genesis.nNonce);
            LogPrintf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
            LogPrintf("block.nBits = %u \n", genesis.nBits);
            LogPrintf("block.nStartLocation = %u \n", genesis.nStartLocation);
            LogPrintf("block.nFinalCalculation = %u \n", genesis.nFinalCalculation);
            consensus.hashGenesisBlock=genesis.GetHash();
        }
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == genesis.GetHash());

        //assert(consensus.hashGenesisBlock == uint256S("0x00afc7c2b815a7424edcafbee0d6645c0cf1104db59f2547e2491c6f8112b84e"));
        //assert(genesis.hashMerkleRoot == uint256S("0x7d885d58c9085601aba2569c3a946a64a61d3032df8442593396861a04244889"));


        vSeeds.push_back(CDNSSeedData("109.94.110.155", "109.94.110.155"));
        vSeeds.push_back(CDNSSeedData("109.94.110.156", "109.94.110.156"));
        vSeeds.push_back(CDNSSeedData("109.94.110.157", "109.94.110.157"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,95);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,40+128);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (Checkpoints::CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("0x00afc7c2b815a7424edcafbee0d6645c0cf1104db59f2547e2491c6f8112b84e")),
            1538397469, // * UNIX timestamp of last checkpoint block
            0,   // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            1000.0     // * estimated number of transactions per day after checkpoint
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.fPowAllowMinDifficultyBlocks = true;
        pchMessageStart[0] = 0x0b;
        pchMessageStart[1] = 0x11;
        pchMessageStart[2] = 0x09;
        pchMessageStart[3] = 0x07;
        vAlertPubKey = ParseHex("045244948ceada9a43a7a5d5f6c56306575a7adfcc07754aec34eea88026d7e7f0acd9089edaac9aa734db5a4eb1aee96b9cedb8260c4ecff4f7db25a5952487aa");
        nDefaultPort = 8989;
        nMinerThreads = 0;
        nMaxTipAge = 0x7fffffff;
        nPruneAfterHeight = 1000;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1457163389;
        genesis.nNonce = 1989891989;



        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == genesis.GetHash());

        //consensus.hashGenesisBlock = genesis.GetHash();
        //assert(consensus.hashGenesisBlock == uint256S("0x000000000933ea01ad0ee984209779baaec3ced90fa3f408719526f8d77f4943"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("westcoast.hodlcoin.com", "westcoast.hodlcoin.com")); //West Coast
        vSeeds.push_back(CDNSSeedData("eastcoast.hodlcoin.com", "eastcoast.hodlcoin.com"));//East Coast
        vSeeds.push_back(CDNSSeedData("europe.hodlcoin.com", "europe.hodlcoin.com")); //Europe
        vSeeds.push_back(CDNSSeedData("asia.hodlcoin.com", "asia.hodlcoin.com"));//Asia
        vSeeds.push_back(CDNSSeedData("174.140.166.133","174.140.166.133"));//Hodl-lay-yee-hoo
        vSeeds.push_back(CDNSSeedData("54.201.171.55", "54.201.171.55"));
        vSeeds.push_back(CDNSSeedData("54.213.104.91", "54.213.104.91"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,40+128);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();


        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        checkpointData = (Checkpoints::CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("00d655aae75ceef9bc13fd8c6168177746ce85286d11ef56de959f4e9b6ff6af"))
            ( 375491, uint256S("0000013e0f3d708a18f787f8b463b4adfebd40af43fa4674e1ac395de8d75e20")),
            1515148272,
            704236,
            10
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nMinerThreads = 1;
        nMaxTipAge = 24 * 60 * 60;
        genesis.nTime = 1296688602;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 2;
        consensus.hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        //assert(consensus.hashGenesisBlock == uint256S("0x0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206"));
        nPruneAfterHeight = 1000;

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (Checkpoints::CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206")),
            0,
            0,
            0
        };
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}

