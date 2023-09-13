import json
from tencentcloud.common import credential  # 这里需要安装腾讯翻译sdk
from tencentcloud.common.profile.client_profile import ClientProfile
from tencentcloud.common.profile.http_profile import HttpProfile
from tencentcloud.common.exception.tencent_cloud_sdk_exception import TencentCloudSDKException
from tencentcloud.tmt.v20180321 import tmt_client, models

def translate(text, source, target):
    try:
        cred = credential.Credential("AKIDz3yhCUbChz5xa0PcmleLr9D2f6JI5g46", "vgHhz99wVpuyqWyDG5yf8NPODpEPN8vY")  # "xxxx"改为SecretId，"yyyyy"改为SecretKey
        httpProfile = HttpProfile()
        httpProfile.endpoint = "tmt.tencentcloudapi.com"

        clientProfile = ClientProfile()
        clientProfile.httpProfile = httpProfile
        client = tmt_client.TmtClient(cred, "ap-beijing", clientProfile)

        req = models.TextTranslateRequest()
        req.SourceText = text # 要翻译的语句
        req.Source = source  # 源语言类型
        req.Target = target  # 目标语言类型
        req.ProjectId = 0

        resp = client.TextTranslate(req)
        data = json.loads(resp.to_json_string())
        return data['TargetText']  # 返回翻译结果作为字符串

    except TencentCloudSDKException as err:
        return str(err)  # 如果发生异常，将异常信息作为字符串返回


# 源语言，支持：
# auto：自动识别（识别为一种语言）
# zh：简体中文
# zh-TW：繁体中文
# en：英语
# ja：日语
# ko：韩语
# fr：法语
# es：西班牙语
# it：意大利语
# de：德语
# tr：土耳其语
# ru：俄语
# pt：葡萄牙语
# vi：越南语
# id：印尼语
# th：泰语
# ms：马来西亚语
# ar：阿拉伯语
# hi：印地语