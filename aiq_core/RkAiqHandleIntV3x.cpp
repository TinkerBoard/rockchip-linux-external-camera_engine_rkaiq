#include "RkAiqHandleIntV3x.h"
#include "RkAiqCore.h"


namespace RkCam {

//ynr v3
void
RkAiqAynrV3HandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAynrHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAynrV3Int());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAynrV3Int());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAynrV3Int());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAynrV3Int());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAynrV3Int());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAynrV3Int());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAynrV3Int());

    EXIT_ANALYZER_FUNCTION();
}


XCamReturn
RkAiqAynrV3HandleInt::updateConfig(bool needSync)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync)
        mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_aynrV3_SetAttrib(mAlgoCtx, &mCurAtt, false);
        sendSignal();
    }

    if(updateIQpara) {
        mCurIQPara = mNewIQPara;
        updateIQpara = false;
        // TODO
        //rk_aiq_uapi_asharp_SetIQpara_V3(mAlgoCtx, &mCurIQPara, false);
        sendSignal();
    }

    if(updateStrength) {
        mCurStrength = mNewStrength;
        updateStrength = false;
        rk_aiq_uapi_aynrV3_SetLumaSFStrength(mAlgoCtx, mCurStrength);
        sendSignal();
    }

    if (needSync)
        mCfgMutex.unlock();


    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAynrV3HandleInt::setAttrib(rk_aiq_ynr_attrib_v3_t *att)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    //TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, att, sizeof(rk_aiq_ynr_attrib_v3_t))) {
        mNewAtt = *att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAynrV3HandleInt::getAttrib(rk_aiq_ynr_attrib_v3_t *att)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_aynrV3_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAynrV3HandleInt::setIQPara(rk_aiq_ynr_IQPara_V3_t *para)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    //TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurIQPara, para, sizeof(rk_aiq_ynr_IQPara_V3_t))) {
        mNewIQPara = *para;
        updateIQpara = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAynrV3HandleInt::getIQPara(rk_aiq_ynr_IQPara_V3_t *para)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    // rk_aiq_uapi_asharp_GetIQpara(mAlgoCtx, para);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}


XCamReturn
RkAiqAynrV3HandleInt::setStrength(float fPercent)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();

    mNewStrength = fPercent;
    updateStrength = true;
    waitSignal();

    mCfgMutex.unlock();
    EXIT_ANALYZER_FUNCTION();
    return ret;
}


XCamReturn
RkAiqAynrV3HandleInt::getStrength(float *pPercent)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_aynrV3_GetLumaSFStrength(mAlgoCtx, pPercent);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}


XCamReturn
RkAiqAynrV3HandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAynrHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "aynr handle prepare failed");

    RkAiqAlgoConfigAynrV3Int* aynr_config_int = (RkAiqAlgoConfigAynrV3Int*)mConfig;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;

    aynr_config_int->stAynrConfig.rawWidth = sharedCom->snsDes.isp_acq_width;
    aynr_config_int->stAynrConfig.rawHeight = sharedCom->snsDes.isp_acq_height;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "aynr algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAynrV3HandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAynrV3Int* aynr_pre_int = (RkAiqAlgoPreAynrV3Int*)mPreInParam;
    RkAiqAlgoPreResAynrV3Int* aynr_pre_res_int = (RkAiqAlgoPreResAynrV3Int*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats = shared->ispStats;

    ret = RkAiqAynrHandle::preProcess();
    if (ret) {
        comb->aynr_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aynr handle preProcess failed");
    }

    comb->aynr_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "aynr algo pre_process failed");
    // set result to mAiqCore
    comb->aynr_pre_res = (RkAiqAlgoPreResAynr*)aynr_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAynrV3HandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAynrV3Int* aynr_proc_int = (RkAiqAlgoProcAynrV3Int*)mProcInParam;
    RkAiqAlgoProcResAynrV3Int* aynr_proc_res_int = (RkAiqAlgoProcResAynrV3Int*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats = shared->ispStats;
    static int aynr_proc_framecnt = 0;
    aynr_proc_framecnt++;

    ret = RkAiqAynrHandle::processing();
    if (ret) {
        comb->aynr_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aynr handle processing failed");
    }

    comb->aynr_proc_res = NULL;

    // TODO: fill procParam
    aynr_proc_int->iso = sharedCom->iso;
    aynr_proc_int->hdr_mode = sharedCom->working_mode;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "aynr algo processing failed");

    comb->aynr_proc_res = (RkAiqAlgoProcResAynr*)aynr_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAynrV3HandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAynrV3Int* aynr_post_int = (RkAiqAlgoPostAynrV3Int*)mPostInParam;
    RkAiqAlgoPostResAynrV3Int* aynr_post_res_int = (RkAiqAlgoPostResAynrV3Int*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats = shared->ispStats;

    ret = RkAiqAynrHandle::postProcess();
    if (ret) {
        comb->aynr_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aynr handle postProcess failed");
        return ret;
    }

    comb->aynr_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "aynr algo post_process failed");
    // set result to mAiqCore
    comb->aynr_post_res = (RkAiqAlgoPostResAynr*)aynr_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAcnrV2HandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAcnrHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAcnrV2Int());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAcnrV2Int());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAcnrV2Int());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAcnrV2Int());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAcnrV2Int());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAcnrV2Int());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAcnrV2Int());

    EXIT_ANALYZER_FUNCTION();
}


XCamReturn
RkAiqAcnrV2HandleInt::updateConfig(bool needSync)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync)
        mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_acnrV2_SetAttrib(mAlgoCtx, &mCurAtt, false);
        sendSignal();
    }

    if(updateIQpara) {
        mCurIQPara = mNewIQPara;
        updateIQpara = false;
        // TODO
        //rk_aiq_uapi_asharp_SetIQpara_V3(mAlgoCtx, &mCurIQPara, false);
        sendSignal();
    }

    if(updateStrength) {
        mCurStrength = mNewStrength;
        updateStrength = false;
        rk_aiq_uapi_acnrV2_SetChromaSFStrength(mAlgoCtx, mCurStrength);
        sendSignal();
    }

    if (needSync)
        mCfgMutex.unlock();


    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAcnrV2HandleInt::setAttrib(rk_aiq_cnr_attrib_v2_t *att)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    //TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, att, sizeof(rk_aiq_cnr_attrib_v2_t))) {
        mNewAtt = *att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAcnrV2HandleInt::getAttrib(rk_aiq_cnr_attrib_v2_t *att)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_acnrV2_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAcnrV2HandleInt::setIQPara(rk_aiq_cnr_IQPara_V2_t *para)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    //TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurIQPara, para, sizeof(rk_aiq_cnr_IQPara_V2_t))) {
        mNewIQPara = *para;
        updateIQpara = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAcnrV2HandleInt::getIQPara(rk_aiq_cnr_IQPara_V2_t *para)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    // rk_aiq_uapi_asharp_GetIQpara(mAlgoCtx, para);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}


XCamReturn
RkAiqAcnrV2HandleInt::setStrength(float fPercent)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();


    mNewStrength = fPercent;
    updateStrength = true;
    waitSignal();


    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();

    return ret;

}


XCamReturn
RkAiqAcnrV2HandleInt::getStrength(float *pPercent)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_acnrV2_GetChromaSFStrength(mAlgoCtx, pPercent);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}


XCamReturn
RkAiqAcnrV2HandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAcnrHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "acnr handle prepare failed");

    RkAiqAlgoConfigAcnrV1Int* acnr_config_int = (RkAiqAlgoConfigAcnrV1Int*)mConfig;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "acnr algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAcnrV2HandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAcnrV2Int* acnr_pre_int = (RkAiqAlgoPreAcnrV2Int*)mPreInParam;
    RkAiqAlgoPreResAcnrV2Int* acnr_pre_res_int = (RkAiqAlgoPreResAcnrV2Int*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats = shared->ispStats;

    ret = RkAiqAcnrHandle::preProcess();
    if (ret) {
        comb->acnr_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "acnr handle preProcess failed");
    }

    comb->acnr_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "acnr algo pre_process failed");
    // set result to mAiqCore
    comb->acnr_pre_res = (RkAiqAlgoPreResAcnr*)acnr_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAcnrV2HandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAcnrV2Int* acnr_proc_int = (RkAiqAlgoProcAcnrV2Int*)mProcInParam;
    RkAiqAlgoProcResAcnrV2Int* acnr_proc_res_int = (RkAiqAlgoProcResAcnrV2Int*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats = shared->ispStats;
    static int acnr_proc_framecnt = 0;
    acnr_proc_framecnt++;

    ret = RkAiqAcnrHandle::processing();
    if (ret) {
        comb->acnr_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "acnr handle processing failed");
    }

    comb->acnr_proc_res = NULL;

    // TODO: fill procParam
    acnr_proc_int->iso = sharedCom->iso;
    acnr_proc_int->hdr_mode = sharedCom->working_mode;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "aynr algo processing failed");

    comb->acnr_proc_res = (RkAiqAlgoProcResAcnr*)acnr_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAcnrV2HandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAcnrV2Int* acnr_post_int = (RkAiqAlgoPostAcnrV2Int*)mPostInParam;
    RkAiqAlgoPostResAcnrV2Int* acnr_post_res_int = (RkAiqAlgoPostResAcnrV2Int*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats = shared->ispStats;

    ret = RkAiqAcnrHandle::postProcess();
    if (ret) {
        comb->aynr_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "acnr handle postProcess failed");
        return ret;
    }

    comb->acnr_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "acnr algo post_process failed");
    // set result to mAiqCore
    comb->acnr_post_res = (RkAiqAlgoPostResAcnr*)acnr_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void
RkAiqAsharpV4HandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAsharpHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAsharpV4Int());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAsharpV4Int());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAsharpV4Int());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAsharpV4Int());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAsharpV4Int());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAsharpV4Int());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAsharpV4Int());

    EXIT_ANALYZER_FUNCTION();
}


XCamReturn
RkAiqAsharpV4HandleInt::updateConfig(bool needSync)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync)
        mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_asharpV4_SetAttrib(mAlgoCtx, &mCurAtt, false);
        sendSignal();
    }

    if(updateIQpara) {
        mCurIQPara = mNewIQPara;
        updateIQpara = false;
        // TODO
        //rk_aiq_uapi_asharp_SetIQpara_V3(mAlgoCtx, &mCurIQPara, false);
        sendSignal();
    }

    if(updateStrength) {
        mCurStrength = mNewStrength;
        updateStrength = false;
        rk_aiq_uapi_asharpV4_SetStrength(mAlgoCtx, mCurStrength);
        sendSignal();
    }

    if (needSync)
        mCfgMutex.unlock();


    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAsharpV4HandleInt::setAttrib(rk_aiq_sharp_attrib_v4_t *att)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    //TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, att, sizeof(rk_aiq_sharp_attrib_v4_t))) {
        mNewAtt = *att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAsharpV4HandleInt::getAttrib(rk_aiq_sharp_attrib_v4_t *att)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_asharpV4_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAsharpV4HandleInt::setIQPara(rk_aiq_sharp_IQPara_V4_t *para)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    //TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurIQPara, para, sizeof(rk_aiq_sharp_IQPara_V4_t))) {
        mNewIQPara = *para;
        updateIQpara = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAsharpV4HandleInt::getIQPara(rk_aiq_sharp_IQPara_V4_t *para)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    // rk_aiq_uapi_asharp_GetIQpara(mAlgoCtx, para);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}


XCamReturn
RkAiqAsharpV4HandleInt::setStrength(float fPercent)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();


    mNewStrength = fPercent;
    updateStrength = true;
    waitSignal();


    mCfgMutex.unlock();
    EXIT_ANALYZER_FUNCTION();
    return ret;
}


XCamReturn
RkAiqAsharpV4HandleInt::getStrength(float *pPercent)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_asharpV4_GetStrength(mAlgoCtx, pPercent);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}


XCamReturn
RkAiqAsharpV4HandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAsharpHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "asharp handle prepare failed");

    RkAiqAlgoConfigAsharpV4Int* asharp_config_int = (RkAiqAlgoConfigAsharpV4Int*)mConfig;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "asharp algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAsharpV4HandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAsharpV4Int* asharp_pre_int = (RkAiqAlgoPreAsharpV4Int*)mPreInParam;
    RkAiqAlgoPreResAsharpV4Int* asharp_pre_res_int = (RkAiqAlgoPreResAsharpV4Int*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats = shared->ispStats;

    ret = RkAiqAsharpHandle::preProcess();
    if (ret) {
        comb->asharp_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "asharp handle preProcess failed");
    }

    comb->asharp_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "asharp algo pre_process failed");
    // set result to mAiqCore
    comb->asharp_pre_res = (RkAiqAlgoPreResAsharp*)asharp_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAsharpV4HandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAsharpV4Int* asharp_proc_int = (RkAiqAlgoProcAsharpV4Int*)mProcInParam;
    RkAiqAlgoProcResAsharpV4Int* asharp_proc_res_int = (RkAiqAlgoProcResAsharpV4Int*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats = shared->ispStats;
    static int asharp_proc_framecnt = 0;
    asharp_proc_framecnt++;

    ret = RkAiqAsharpHandle::processing();
    if (ret) {
        comb->asharp_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "asharp handle processing failed");
    }

    comb->asharp_proc_res = NULL;

    // TODO: fill procParam
    asharp_proc_int->iso = sharedCom->iso;
    asharp_proc_int->hdr_mode = sharedCom->working_mode;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "asharp algo processing failed");

    comb->asharp_proc_res = (RkAiqAlgoProcResAsharp*)asharp_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAsharpV4HandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAsharpV4Int* asharp_post_int = (RkAiqAlgoPostAsharpV4Int*)mPostInParam;
    RkAiqAlgoPostResAsharpV4Int* asharp_post_res_int = (RkAiqAlgoPostResAsharpV4Int*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats = shared->ispStats;

    ret = RkAiqAsharpHandle::postProcess();
    if (ret) {
        comb->asharp_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "asharp handle postProcess failed");
        return ret;
    }

    comb->asharp_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "asharp algo post_process failed");
    // set result to mAiqCore
    comb->asharp_post_res = (RkAiqAlgoPostResAsharp*)asharp_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}


void
RkAiqAbayer2dnrV2HandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqArawnrHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAbayer2dnrV2Int());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAbayer2dnrV2Int());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAbayer2dnrV2Int());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAbayer2dnrV2Int());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAbayer2dnrV2Int());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAbayer2dnrV2Int());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAbayer2dnrV2Int());

    EXIT_ANALYZER_FUNCTION();
}


XCamReturn
RkAiqAbayer2dnrV2HandleInt::updateConfig(bool needSync)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync)
        mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_abayer2dnrV2_SetAttrib(mAlgoCtx, &mCurAtt, false);
        sendSignal();
    }

    if(updateIQpara) {
        mCurIQPara = mNewIQPara;
        updateIQpara = false;
        // TODO
        //rk_aiq_uapi_asharp_SetIQpara_V3(mAlgoCtx, &mCurIQPara, false);
        sendSignal();
    }

    if(updateStrength) {
        mCurStrength = mNewStrength;
        updateStrength = false;
        rk_aiq_uapi_abayer2dnrV2_SetStrength(mAlgoCtx, mCurStrength);
        sendSignal();
    }

    if (needSync)
        mCfgMutex.unlock();


    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAbayer2dnrV2HandleInt::setAttrib(rk_aiq_bayer2dnr_attrib_v2_t *att)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    //TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, att, sizeof(rk_aiq_bayer2dnr_attrib_v2_t))) {
        mNewAtt = *att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAbayer2dnrV2HandleInt::getAttrib(rk_aiq_bayer2dnr_attrib_v2_t *att)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_abayer2dnrV2_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAbayer2dnrV2HandleInt::setIQPara(rk_aiq_bayer2dnr_IQPara_V2_t *para)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    //TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurIQPara, para, sizeof(rk_aiq_bayer2dnr_IQPara_V2_t))) {
        mNewIQPara = *para;
        updateIQpara = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAbayer2dnrV2HandleInt::getIQPara(rk_aiq_bayer2dnr_IQPara_V2_t *para)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    // rk_aiq_uapi_asharp_GetIQpara(mAlgoCtx, para);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}


XCamReturn
RkAiqAbayer2dnrV2HandleInt::setStrength(float fPercent)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();


    mNewStrength = fPercent;
    updateStrength = true;
    waitSignal();


    mCfgMutex.unlock();
    EXIT_ANALYZER_FUNCTION();
    return ret;
}


XCamReturn
RkAiqAbayer2dnrV2HandleInt::getStrength(float *pPercent)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_abayer2dnrV2_GetStrength(mAlgoCtx, pPercent);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}




XCamReturn
RkAiqAbayer2dnrV2HandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqArawnrHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "arawnr handle prepare failed");

    RkAiqAlgoConfigAbayer2dnrV2Int* aynr_config_int = (RkAiqAlgoConfigAbayer2dnrV2Int*)mConfig;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "arawnr algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAbayer2dnrV2HandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAbayer2dnrV2Int* arawnr_pre_int = (RkAiqAlgoPreAbayer2dnrV2Int*)mPreInParam;
    RkAiqAlgoPreResAbayer2dnrV2Int* arawnr_pre_res_int = (RkAiqAlgoPreResAbayer2dnrV2Int*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats = shared->ispStats;

    ret = RkAiqArawnrHandle::preProcess();
    if (ret) {
        comb->arawnr_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "arawnr handle preProcess failed");
    }

    comb->arawnr_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "arawnr algo pre_process failed");
    // set result to mAiqCore
    comb->arawnr_pre_res = (RkAiqAlgoPreResArawnr*)arawnr_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAbayer2dnrV2HandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAbayer2dnrV2Int* arawnr_proc_int = (RkAiqAlgoProcAbayer2dnrV2Int*)mProcInParam;
    RkAiqAlgoProcResAbayer2dnrV2Int* arawnr_proc_res_int = (RkAiqAlgoProcResAbayer2dnrV2Int*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats = shared->ispStats;
    static int arawnr_proc_framecnt = 0;
    arawnr_proc_framecnt++;

    ret = RkAiqArawnrHandle::processing();
    if (ret) {
        comb->arawnr_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aynr handle processing failed");
    }

    comb->arawnr_proc_res = NULL;

    // TODO: fill procParam
    arawnr_proc_int->iso = sharedCom->iso;
    arawnr_proc_int->hdr_mode = sharedCom->working_mode;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "aynr algo processing failed");

    comb->arawnr_proc_res = (RkAiqAlgoProcResArawnr*)arawnr_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAbayer2dnrV2HandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAbayer2dnrV2Int* arawnr_post_int = (RkAiqAlgoPostAbayer2dnrV2Int*)mPostInParam;
    RkAiqAlgoPostResAbayer2dnrV2Int* arawnr_post_res_int = (RkAiqAlgoPostResAbayer2dnrV2Int*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats = shared->ispStats;

    ret = RkAiqArawnrHandle::postProcess();
    if (ret) {
        comb->arawnr_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "arawnr handle postProcess failed");
        return ret;
    }

    comb->arawnr_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "arawnr algo post_process failed");
    // set result to mAiqCore
    comb->arawnr_post_res = (RkAiqAlgoPostResArawnr*)arawnr_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}



//bayertnrV2
void
RkAiqAbayertnrV2HandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAmfnrHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAbayertnrV2Int());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAbayertnrV2Int());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAbayertnrV2Int());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAbayertnrV2Int());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAbayertnrV2Int());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAbayertnrV2Int());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAbayertnrV2Int());

    EXIT_ANALYZER_FUNCTION();
}


XCamReturn
RkAiqAbayertnrV2HandleInt::updateConfig(bool needSync)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync)
        mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_abayertnrV2_SetAttrib(mAlgoCtx, &mCurAtt, false);
        sendSignal();
    }

    if(updateIQpara) {
        mCurIQPara = mNewIQPara;
        updateIQpara = false;
        // TODO
        //rk_aiq_uapi_asharp_SetIQpara_V3(mAlgoCtx, &mCurIQPara, false);
        sendSignal();
    }

    if(updateStrength) {
        mCurStrength = mNewStrength;
        updateStrength = false;
        rk_aiq_uapi_abayertnrV2_SetStrength(mAlgoCtx, mCurStrength);
        sendSignal();
    }

    if (needSync)
        mCfgMutex.unlock();


    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAbayertnrV2HandleInt::setAttrib(rk_aiq_bayertnr_attrib_v2_t *att)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    //TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, att, sizeof(rk_aiq_bayertnr_attrib_v2_t))) {
        mNewAtt = *att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAbayertnrV2HandleInt::getAttrib(rk_aiq_bayertnr_attrib_v2_t *att)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_abayertnrV2_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAbayertnrV2HandleInt::setIQPara(rk_aiq_bayertnr_IQPara_V2_t *para)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    //TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurIQPara, para, sizeof(rk_aiq_bayertnr_IQPara_V2_t))) {
        mNewIQPara = *para;
        updateIQpara = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAbayertnrV2HandleInt::getIQPara(rk_aiq_bayertnr_IQPara_V2_t *para)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    // rk_aiq_uapi_asharp_GetIQpara(mAlgoCtx, para);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}


XCamReturn
RkAiqAbayertnrV2HandleInt::setStrength(float fPercent)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();


    mNewStrength = fPercent;
    updateStrength = true;
    waitSignal();


    mCfgMutex.unlock();
    EXIT_ANALYZER_FUNCTION();
    return ret;
}


XCamReturn
RkAiqAbayertnrV2HandleInt::getStrength(float *pPercent)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_abayertnrV2_GetStrength(mAlgoCtx, pPercent);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}




XCamReturn
RkAiqAbayertnrV2HandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAmfnrHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "arawnr handle prepare failed");

    RkAiqAlgoConfigAbayertnrV2Int* abayertnr_config_int = (RkAiqAlgoConfigAbayertnrV2Int*)mConfig;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "arawnr algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAbayertnrV2HandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAbayertnrV2Int* abayertnr_pre_int = (RkAiqAlgoPreAbayertnrV2Int*)mPreInParam;
    RkAiqAlgoPreResAbayertnrV2Int* abayertnr_pre_res_int = (RkAiqAlgoPreResAbayertnrV2Int*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats = shared->ispStats;

    ret = RkAiqAmfnrHandle::preProcess();
    if (ret) {
        comb->amfnr_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "arawnr handle preProcess failed");
    }

    comb->amfnr_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "arawnr algo pre_process failed");
    // set result to mAiqCore
    comb->amfnr_pre_res = (RkAiqAlgoPreResAmfnr*)abayertnr_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAbayertnrV2HandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAbayertnrV2Int* abayertnr_proc_int = (RkAiqAlgoProcAbayertnrV2Int*)mProcInParam;
    RkAiqAlgoProcResAbayertnrV2Int* abayertnr_proc_res_int = (RkAiqAlgoProcResAbayertnrV2Int*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats = shared->ispStats;
    static int abayertnr_proc_framecnt = 0;
    abayertnr_proc_framecnt++;

    ret = RkAiqAmfnrHandle::processing();
    if (ret) {
        comb->amfnr_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aynr handle processing failed");
    }

    comb->amfnr_proc_res = NULL;

    // TODO: fill procParam
    abayertnr_proc_int->iso = sharedCom->iso;
    abayertnr_proc_int->hdr_mode = sharedCom->working_mode;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "aynr algo processing failed");

    comb->amfnr_proc_res = (RkAiqAlgoProcResAmfnr*)abayertnr_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAbayertnrV2HandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAbayer2dnrV2Int* abayertnr_post_int = (RkAiqAlgoPostAbayer2dnrV2Int*)mPostInParam;
    RkAiqAlgoPostResAbayer2dnrV2Int* abayertnr_post_res_int = (RkAiqAlgoPostResAbayer2dnrV2Int*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats = shared->ispStats;

    ret = RkAiqAmfnrHandle::postProcess();
    if (ret) {
        comb->amfnr_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "arawnr handle postProcess failed");
        return ret;
    }

    comb->amfnr_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "arawnr algo post_process failed");
    // set result to mAiqCore
    comb->amfnr_post_res = (RkAiqAlgoPostResAmfnr*)abayertnr_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}


//again v2
void
RkAiqAgainV2HandleInt::init()
{
    ENTER_ANALYZER_FUNCTION();

    RkAiqAgainHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAgainV2Int());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAgainV2Int());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAgainV2Int());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAgainV2Int());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAgainV2Int());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAgainV2Int());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAgainV2Int());

    EXIT_ANALYZER_FUNCTION();
}


XCamReturn
RkAiqAgainV2HandleInt::updateConfig(bool needSync)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync)
        mCfgMutex.lock();


    if (needSync)
        mCfgMutex.unlock();


    EXIT_ANALYZER_FUNCTION();
    return ret;
}


XCamReturn
RkAiqAgainV2HandleInt::prepare()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAgainHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "again handle prepare failed");

    RkAiqAlgoConfigAgainV2Int* again_config_int = (RkAiqAlgoConfigAgainV2Int*)mConfig;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "again algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAgainV2HandleInt::preProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAgainV2Int* again_pre_int = (RkAiqAlgoPreAgainV2Int*)mPreInParam;
    RkAiqAlgoPreResAgainV2Int* again_pre_res_int = (RkAiqAlgoPreResAgainV2Int*)mPreOutParam;

    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats = shared->ispStats;


    ret = RkAiqAgainHandle::preProcess();
    if (ret) {
        comb->again_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "again handle preProcess failed");
    }

    comb->again_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "again algo pre_process failed");
    // set result to mAiqCore
    comb->again_pre_res = (RkAiqAlgoPreResAgain*)again_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqAgainV2HandleInt::processing()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAgainV2Int* again_proc_int = (RkAiqAlgoProcAgainV2Int*)mProcInParam;
    RkAiqAlgoProcResAgainV2Int* again_proc_res_int = (RkAiqAlgoProcResAgainV2Int*)mProcOutParam;

    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats = shared->ispStats;

    static int auvnr_proc_framecnt = 0;
    auvnr_proc_framecnt++;

    ret = RkAiqAgainHandle::processing();
    if (ret) {
        comb->again_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "again handle processing failed");
    }

    comb->again_proc_res = NULL;

    // TODO: fill procParam
    again_proc_int->iso = sharedCom->iso;
    again_proc_int->hdr_mode = sharedCom->working_mode;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "again algo processing failed");

    comb->again_proc_res = (RkAiqAlgoProcResAgain*)again_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn
RkAiqAgainV2HandleInt::postProcess()
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAgainV2Int* again_post_int = (RkAiqAlgoPostAgainV2Int*)mPostInParam;
    RkAiqAlgoPostResAgainV2Int* again_post_res_int = (RkAiqAlgoPostResAgainV2Int*)mPostOutParam;

    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats = shared->ispStats;

    ret = RkAiqAgainHandle::postProcess();
    if (ret) {
        comb->again_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "auvnr handle postProcess failed");
        return ret;
    }

    comb->again_post_res = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "auvnr algo post_process failed");
    // set result to mAiqCore
    comb->again_post_res = (RkAiqAlgoPostResAgain*)again_post_res_int ;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}


}; //namespace RkCam


