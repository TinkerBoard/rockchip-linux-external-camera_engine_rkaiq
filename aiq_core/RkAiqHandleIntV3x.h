#ifndef _RK_AIQ_HANDLE_INT_V3_H_
#define _RK_AIQ_HANDLE_INT_V3_H_

#include "RkAiqHandleInt.h"

#include "aynr3/rk_aiq_uapi_aynr_int_v3.h"
#include "acnr2/rk_aiq_uapi_acnr_int_v2.h"
#include "asharp4/rk_aiq_uapi_asharp_int_v4.h"
#include "abayer2dnr2/rk_aiq_uapi_abayer2dnr_int_v2.h"
#include "abayertnr2/rk_aiq_uapi_abayertnr_int_v2.h"
#include "again2/rk_aiq_uapi_again_int_v2.h"

namespace RkCam {

// aynr v2
class RkAiqAynrV3HandleInt:
    virtual public RkAiqHandle {
public:
    explicit RkAiqAynrV3HandleInt(RkAiqAlgoDesComm* des, RkAiqCore* aiqCore)
        : RkAiqHandle(des, aiqCore) {
        memset(&mCurAtt, 0, sizeof(rk_aiq_ynr_attrib_v3_t));
        memset(&mNewAtt, 0, sizeof(rk_aiq_ynr_attrib_v3_t));
    };
    virtual ~RkAiqAynrV3HandleInt() {
        RkAiqHandle::deInit();
    };
    virtual XCamReturn updateConfig(bool needSync);
    virtual XCamReturn prepare();
    virtual XCamReturn preProcess();
    virtual XCamReturn processing();
    virtual XCamReturn postProcess();
    virtual XCamReturn genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params);
    // TODO add algo specific methords, this is a sample
    XCamReturn setAttrib(rk_aiq_ynr_attrib_v3_t *att);
    XCamReturn getAttrib(rk_aiq_ynr_attrib_v3_t *att);
    XCamReturn setStrength(float fPercent);
    XCamReturn getStrength(float *pPercent);
    XCamReturn setIQPara(rk_aiq_ynr_IQPara_V3_t *pPara);
    XCamReturn getIQPara(rk_aiq_ynr_IQPara_V3_t *pPara);
protected:
    virtual void init();
    virtual void deInit() {
        RkAiqHandle::deInit();
    };
private:
    // TODO
    rk_aiq_ynr_attrib_v3_t mCurAtt;
    rk_aiq_ynr_attrib_v3_t mNewAtt;
    rk_aiq_ynr_IQPara_V3_t mCurIQPara;
    rk_aiq_ynr_IQPara_V3_t mNewIQPara;
    float mCurStrength;
    float mNewStrength;
    bool updateIQpara = false;
    bool updateStrength = false;
};


// acnr v2
class RkAiqAcnrV2HandleInt:
    virtual public RkAiqHandle {
public:
    explicit RkAiqAcnrV2HandleInt(RkAiqAlgoDesComm* des, RkAiqCore* aiqCore)
        : RkAiqHandle(des, aiqCore) {
        memset(&mCurAtt, 0, sizeof(rk_aiq_cnr_attrib_v2_t));
        memset(&mNewAtt, 0, sizeof(rk_aiq_cnr_attrib_v2_t));
    };
    virtual ~RkAiqAcnrV2HandleInt() {
        RkAiqHandle::deInit();
    };
    virtual XCamReturn updateConfig(bool needSync);
    virtual XCamReturn prepare();
    virtual XCamReturn preProcess();
    virtual XCamReturn processing();
    virtual XCamReturn postProcess();
    virtual XCamReturn genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params);
    // TODO add algo specific methords, this is a sample
    XCamReturn setAttrib(rk_aiq_cnr_attrib_v2_t *att);
    XCamReturn getAttrib(rk_aiq_cnr_attrib_v2_t *att);
    XCamReturn setStrength(float fPercent);
    XCamReturn getStrength(float *pPercent);
    XCamReturn setIQPara(rk_aiq_cnr_IQPara_V2_t *pPara);
    XCamReturn getIQPara(rk_aiq_cnr_IQPara_V2_t *pPara);
protected:
    virtual void init();
    virtual void deInit() {
        RkAiqHandle::deInit();
    };
private:
    // TODO
    rk_aiq_cnr_attrib_v2_t mCurAtt;
    rk_aiq_cnr_attrib_v2_t mNewAtt;
    rk_aiq_cnr_IQPara_V2_t mCurIQPara;
    rk_aiq_cnr_IQPara_V2_t mNewIQPara;
    float mCurStrength;
    float mNewStrength;
    bool updateIQpara = false;
    bool updateStrength = false;
};

// asharp v3
class RkAiqAsharpV4HandleInt:
    virtual public RkAiqHandle {
public:
    explicit RkAiqAsharpV4HandleInt(RkAiqAlgoDesComm* des, RkAiqCore* aiqCore)
        : RkAiqHandle(des, aiqCore) {
        memset(&mCurAtt, 0, sizeof(rk_aiq_sharp_attrib_v4_t));
        memset(&mNewAtt, 0, sizeof(rk_aiq_sharp_attrib_v4_t));
    };
    virtual ~RkAiqAsharpV4HandleInt() {
        RkAiqHandle::deInit();
    };
    virtual XCamReturn updateConfig(bool needSync);
    virtual XCamReturn prepare();
    virtual XCamReturn preProcess();
    virtual XCamReturn processing();
    virtual XCamReturn postProcess();
    virtual XCamReturn genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params);
    // TODO add algo specific methords, this is a sample
    XCamReturn setAttrib(rk_aiq_sharp_attrib_v4_t *att);
    XCamReturn getAttrib(rk_aiq_sharp_attrib_v4_t *att);
    XCamReturn setStrength(float fPercent);
    XCamReturn getStrength(float *pPercent);
    XCamReturn setIQPara(rk_aiq_sharp_IQPara_V4_t *para);
    XCamReturn getIQPara(rk_aiq_sharp_IQPara_V4_t *para);

protected:
    virtual void init();
    virtual void deInit() {
        RkAiqHandle::deInit();
    };
private:
    // TODO
    rk_aiq_sharp_attrib_v4_t mCurAtt;
    rk_aiq_sharp_attrib_v4_t mNewAtt;
    rk_aiq_sharp_IQPara_V4_t mCurIQPara;
    rk_aiq_sharp_IQPara_V4_t mNewIQPara;
    float mCurStrength;
    float mNewStrength;
    bool updateIQpara = false;
    bool updateStrength = false;

};

// aynr v2
class RkAiqAbayer2dnrV2HandleInt:
    virtual public RkAiqHandle {
public:
    explicit RkAiqAbayer2dnrV2HandleInt(RkAiqAlgoDesComm* des, RkAiqCore* aiqCore)
        : RkAiqHandle(des, aiqCore) {
        memset(&mCurAtt, 0, sizeof(rk_aiq_bayer2dnr_attrib_v2_t));
        memset(&mNewAtt, 0, sizeof(rk_aiq_bayer2dnr_attrib_v2_t));
    };
    virtual ~RkAiqAbayer2dnrV2HandleInt() {
        RkAiqHandle::deInit();
    };
    virtual XCamReturn updateConfig(bool needSync);
    virtual XCamReturn prepare();
    virtual XCamReturn preProcess();
    virtual XCamReturn processing();
    virtual XCamReturn postProcess();
    virtual XCamReturn genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params);
    // TODO add algo specific methords, this is a sample
    XCamReturn setAttrib(rk_aiq_bayer2dnr_attrib_v2_t *att);
    XCamReturn getAttrib(rk_aiq_bayer2dnr_attrib_v2_t *att);
    XCamReturn setStrength(float fPercent);
    XCamReturn getStrength(float *pPercent);
    XCamReturn setIQPara(rk_aiq_bayer2dnr_IQPara_V2_t *pPara);
    XCamReturn getIQPara(rk_aiq_bayer2dnr_IQPara_V2_t *pPara);
protected:
    virtual void init();
    virtual void deInit() {
        RkAiqHandle::deInit();
    };
private:
    // TODO
    rk_aiq_bayer2dnr_attrib_v2_t mCurAtt;
    rk_aiq_bayer2dnr_attrib_v2_t mNewAtt;
    rk_aiq_bayer2dnr_IQPara_V2_t mCurIQPara;
    rk_aiq_bayer2dnr_IQPara_V2_t mNewIQPara;
    float mCurStrength;
    float mNewStrength;
    bool updateIQpara = false;
    bool updateStrength = false;
};

// aynr v2
class RkAiqAbayertnrV2HandleInt:
    virtual public RkAiqHandle {
public:
    explicit RkAiqAbayertnrV2HandleInt(RkAiqAlgoDesComm* des, RkAiqCore* aiqCore)
        : RkAiqHandle(des, aiqCore) {
        memset(&mCurAtt, 0, sizeof(rk_aiq_bayertnr_attrib_v2_t));
        memset(&mNewAtt, 0, sizeof(rk_aiq_bayertnr_attrib_v2_t));
    };
    virtual ~RkAiqAbayertnrV2HandleInt() {
        RkAiqHandle::deInit();
    };
    virtual XCamReturn updateConfig(bool needSync);
    virtual XCamReturn prepare();
    virtual XCamReturn preProcess();
    virtual XCamReturn processing();
    virtual XCamReturn postProcess();
    virtual XCamReturn genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params);
    // TODO add algo specific methords, this is a sample
    XCamReturn setAttrib(rk_aiq_bayertnr_attrib_v2_t *att);
    XCamReturn getAttrib(rk_aiq_bayertnr_attrib_v2_t *att);
    XCamReturn setStrength(float fPercent);
    XCamReturn getStrength(float *pPercent);
    XCamReturn setIQPara(rk_aiq_bayertnr_IQPara_V2_t *pPara);
    XCamReturn getIQPara(rk_aiq_bayertnr_IQPara_V2_t *pPara);
protected:
    virtual void init();
    virtual void deInit() {
        RkAiqHandle::deInit();
    };
private:
    // TODO
    rk_aiq_bayertnr_attrib_v2_t mCurAtt;
    rk_aiq_bayertnr_attrib_v2_t mNewAtt;
    rk_aiq_bayertnr_IQPara_V2_t mCurIQPara;
    rk_aiq_bayertnr_IQPara_V2_t mNewIQPara;
    float mCurStrength;
    float mNewStrength;
    bool updateIQpara = false;
    bool updateStrength = false;
};

// again v1
class RkAiqAgainV2HandleInt:
    virtual public RkAiqHandle {
public:
    explicit RkAiqAgainV2HandleInt(RkAiqAlgoDesComm* des, RkAiqCore* aiqCore)
        : RkAiqHandle(des, aiqCore) {}
    virtual ~RkAiqAgainV2HandleInt() {
        RkAiqHandle::deInit();
    };
    virtual XCamReturn updateConfig(bool needSync);
    virtual XCamReturn prepare();
    virtual XCamReturn preProcess();
    virtual XCamReturn processing();
    virtual XCamReturn postProcess();
    virtual XCamReturn genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params);

protected:
    virtual void init();
    virtual void deInit() {
        RkAiqHandle::deInit();
    };
private:

};

}

#endif

