// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018 The CTSC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "bignum.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"


//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
// height, hash
// CTSC: 2018-11-02 17:43:21 UpdateTip: new best=0000022a395f7e7f9d5c0842144d85f7ec9cee0646be2afe82d9747d32fce8c6  height=350  log2_work=30.298571  tx=398  date=2018-11-02 17:43:21 progress=1.000000  cache=21
// CTSC: 2018-11-02 22:06:38 UpdateTip: new best=74cac5790bfb5a0991a1e93233436358a2eab4f0fd8564d2af32397f38687340  height=775  log2_work=42.210303  tx=1111  date=2018-11-02 22:07:23 progress=1.000234  cache=663
// CTSC: 2018-11-03 03:57:19 UpdateTip: new best=e3f27cf0eef836e8872521430a60b5a153d6639fdd09575847fee7a0d004541e  height=1250  log2_work=54.302405  tx=2061  date=2018-11-03 03:57:36 progress=1.000048  cache=21
// CTSC: 2018-11-03 16:53:13 UpdateTip: new best=d083d834a2180c4745742233d6f4e2281432bf5b84b78bc4c9009f589bb8c229  height=2025  log2_work=56.739531  tx=3615  date=2018-11-03 16:53:50 progress=1.000059  cache=39
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x00000650aaea7384d7c1576f59777f391f924195ae21fd23e5348c921315226b"))
    (350, uint256("0x0000022a395f7e7f9d5c0842144d85f7ec9cee0646be2afe82d9747d32fce8c6"))
    (775, uint256("0x74cac5790bfb5a0991a1e93233436358a2eab4f0fd8564d2af32397f38687340"))
    (1250, uint256("0xe3f27cf0eef836e8872521430a60b5a153d6639fdd09575847fee7a0d004541e"))
    (2025, uint256("0xd083d834a2180c4745742233d6f4e2281432bf5b84b78bc4c9009f589bb8c229"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1541264030,     // * UNIX timestamp of last checkpoint block (the date=)
    3615,              // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
    250             // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0x00000689c9f1fea0e11e39e1e72edc9d46aeac860c1f15ca34cce12f4b529c04"));
    //(600, uint256("0x0"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1538412980, // 2018-10-04 22:15:13
    0,
    25};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x313ff2fd8c889cc3838f1082b2de47593ff9e527a140c7c3d0d0cce9111e1c17"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1536981815,
    0,
    0};

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

/**
 * Main network
 */
class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x89;
        pchMessageStart[1] = 0xb6;
        pchMessageStart[2] = 0xfa;
        pchMessageStart[3] = 0xe1;
        vAlertPubKey = ParseHex("04ef8ffeb0991288956be66ab1dd9a1945460a006189f6f32ed1749940232afe12e2986532ca772d94958b44828f912d8caede0f8f1730dcde9f11cc057f77c8e5");
        nDefaultPort = 51527;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nSubsidyHalvingInterval = 1050000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // CTSC: 1 minute blocks
        nTargetSpacing = 1 * 60;  // CTSC: 1 minute
        nMaturity = 15; // 16 block maturity (+1 elsewhere in code)
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 85000000 * COIN; // CTSC: 85 million max supply

        /** Height or Time Based Activations **/
        nLastPOWBlock = 500; // CTSC: PoW end
        nModifierUpdateBlock = 1; // we use the V2 modifier for CTSC from start

        const char* pszTimestamp = "U.S. News & World Report 10/23/2018 America Owes the Largest Share of Global Debt";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04bfc42ab49f2a26e297988ece66a89cb655508481f0d4f69333307418df88a80e4bfb309b7ccf8a02a2d3f1743e464c199295f04a03aa450ba82fbe4b8a4eb13e") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1540339199;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 21451067;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000650aaea7384d7c1576f59777f391f924195ae21fd23e5348c921315226b"));
        assert(genesis.hashMerkleRoot == uint256("0x470973e4e1c3b449cfa22ef74518dca2acca9a2f44089e7ddec1a8b847cc87dc"));

        // CTSC: 2 seeders
        // Seeding
        vSeeds.push_back(CDNSSeedData("CTSCSeed1", "seed1.ctscoin.net"));             // seed1
        vSeeds.push_back(CDNSSeedData("CTSCSeed2", "seed2.ctscoin.net"));             // seed2
        vSeeds.push_back(CDNSSeedData("CTSCSeed3", "explorer.ctscoin.net"));          // seed3
        
        // CTSC addresses start with 'T'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 66);
        // CTSC script addresses start with '3'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 16);
        // CTSC private keys start with 'K'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 217);
        // CTSC BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2d)(0xa5)(0x37).convert_to_container<std::vector<unsigned char> >();
        // CTSC BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x34)(0x1a).convert_to_container<std::vector<unsigned char> >();
        // CTSC BIP44 coin type is '222' (0x800000de)
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x1f)(0x55).convert_to_container<std::vector<unsigned char> >();

        // CTSC: Not using hardcoded seeds
        //convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKeyOld = "04cc17389379a0e323f53ea504d38cd71f43dc22f597805fed33a51b05ced1a3ae0db84089985f351b3737721736a82f58c8bd529f79c8ffe57e922bda792146ab";
        strSporkKey = "AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBLORqrN93IVkAwhGKtI5oe8SEfNbFkai5";
        nEnforceNewSporkKey = 1535807069; // CTSC: Sporks signed after Saturday, September 1, 2018 1:04:29 PM GMT must use the new spork key
        nRejectOldSporkKey = 1535720669; // CTSC: Reject old spork key after Friday, August 31, 2018 1:04:29 PM GMT
        
        strMasternodePoolDummyAddress = "TcyHQC8MusYAwGzEGaCdra7sZ3FZeChsKe";
        nStartMasternodePayments = 4070908800;

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x46;
        pchMessageStart[1] = 0xa6;
        pchMessageStart[2] = 0x6b;
        pchMessageStart[3] = 0xbb;
        vAlertPubKey = ParseHex("04ef8ffeb0991288956be66ab1dd9a1945460a006189f6f32ed1749940232afe12e2986532ca772d94958b44828f912d8caede0f8f1730dcde9f11cc057f77c8e5");
        nDefaultPort = 41527;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // CTSC: 1 minute
        nTargetSpacing = 1 * 60;  // CTSC: 1 minute
        nLastPOWBlock = 500; // CTSC: PoW end
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 85000000 * COIN; // CTSC: 85 million max supply

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1538412980;
        genesis.nNonce = 24429876;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000689c9f1fea0e11e39e1e72edc9d46aeac860c1f15ca34cce12f4b529c04"));

        vFixedSeeds.clear();
        vSeeds.clear();

        // Testnet CTSC addresses start with 't'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 128);
        // Testnet CTSC script addresses start with '5' or '6'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 12);
        // Testnet private keys start with 'k'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 108);
        // Testnet CTSC BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet CTSC BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet ctsc BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        // CTSC: Not using hardcoded seeds
        //convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKeyOld = "04abb5e65280dda6a113fadfb9877f9c399532245fe1acb61de293ab298034d5084277fab3768774a3b68cbbe5021cc5049ec8c9997a13f64da1afa0bcfb156db1";
        strSporkKey = "AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBLORqrN93IVkAwhGKtI5oe8SEfNbFkai5";
        nEnforceNewSporkKey = 1535807069; // CTSC: Sporks signed after Saturday, September 1, 2018 1:04:29 PM GMT must use the new spork key
        nRejectOldSporkKey = 1535720669; // CTSC: Reject old spork key after Friday, August 31, 2018 1:04:29 PM GMT

        strMasternodePoolDummyAddress = "tcyHQC8MusYAwGzEGaCdra7sZ3FZeChsKe";
        nStartMasternodePayments = 4070908800;
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa4;
        pchMessageStart[1] = 0xcc;
        pchMessageStart[2] = 0xa7;
        pchMessageStart[3] = 0xa9;
        nDefaultPort = 31527;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // CTSC: 1 day
        nTargetSpacing = 1 * 60;        // CTSC: 1 minute
        bnProofOfWorkLimit = ~uint256(0) >> 1;

        genesis.nTime = 1536981815;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 20542302;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x313ff2fd8c889cc3838f1082b2de47593ff9e527a140c7c3d0d0cce9111e1c17"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    // CTSC: TIP: Can force testnet here when needed
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
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
