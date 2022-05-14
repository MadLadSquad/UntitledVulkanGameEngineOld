#pragma once
#include "LocaleConstants.hpp"
#include <iostream>
#include <vector>
#include <Core/Types.hpp>
#include <Core/Defines.hpp>

namespace UVK
{
    class LocaleManager
    {
    public:
        LocaleManager() = default;
        ~LocaleManager() noexcept;
        void openLocaleConfig(bool bEditor = false);
    private:
        friend class Locale;
        static constexpr String localeString[] =
        {
            "af_za", "am_et", "ar_ae", "ar_bh", "ar_dz", "ar_eg","ar_iq",
            "ar_jo","ar_kw","ar_lb","ar_ly","ar_ma","arn_cl",
            "ar_om","ar_qa","ar_sa","ar_sd","ar_sy","ar_tn","ar_ye",
            "as_in","az_az","az_cyrl_az","az_latn_az","ba_ru","be_by",
            "bg_bg","bn_bd","bn_in","bo_cn","br_fr","bs_cyrl_ba",
            "bs_latn_ba","ca_es","co_fr","cs_cz","cy_gb","da_dk","de_at",
            "de_ch","de_de","de_li","de_lu","dsb_de","dv_mv",
            "el_cy","el_gr","en_029","en_au","en_bz","en_ca","en_cb",
            "en_gb","en_ie","en_in","en_jm","en_mt","en_my","en_nz",
            "en_ph","en_sg","en_tt","en_us","en_za","en_zw","es_ar",
            "es_bo","es_cl","es_co","es_cr","es_do","es_ec","es_es",
            "es_gt","es_hn","es_mx","es_ni","es_pa","es_pe","es_pr",
            "es_py","es_sv","es_us","es_uy","es_ve","et_ee","eu_es",
            "fa_ir","fi_fi","fil_ph","fo_fo","fr_be","fr_ca","fr_ch","fr_fr",
            "fr_lu","fr_mc","fy_nl","ga_ie","gd_gb","gd_ie","gl_es",
            "gsw_fr","gu_in","ha_latn_ng","he_il","hi_in","hr_ba","hr_hr",
            "hsb_de","hu_hu","hy_am","id_id","ig_ng","ii_cn",
            "in_id","is_is","it_ch","it_it","iu_cans_ca",
            "iu_latn_ca","iw_il","jp_jp","ka_ge",
            "kk_kz","kl_gl","km_kh","kn_in","kok_in","ko_kr",
            "ky_kg","lb_lu","lo_la","lt_lt","lv_lv","mi_nz",
            "mk_mk","ml_in","mn_mn",
            "mn_mong_cn","moh_ca","mr_in","ms_bn","ms_my","mt_mt",
            "nb_no","ne_np","nl_be","nl_nl","nn_no","no_no",
            "nso_za","oc_fr","or_in",
            "pa_in","pl_pl","prs_af","ps_af","pt_br","pt_pt",
            "qut_gt","quz_bo","quz_ec","quz_pe","rm_ch","ro_mo",
            "ro_ro","ru_mo","ru_ru",
            "rw_rw","sah_ru","sa_in","se_fi","se_no","se_se",
            "si_lk","sk_sk","sl_si","sma_no","sma_se","smj_no",
            "smj_se","smn_fi","sms_fi",
            "sq_al","sr_ba","sr_cs","sr_cyrl_ba","sr_cyrl_cs",
            "sr_cyrl_me","sr_cyrl_rs","sr_latn_ba","sr_latn_cs","sr_latn_me",
            "sr_latn_rs","sr_me","sr_rs","sr_sp","sv_fi",
            "sv_se","sw_ke","syr_sy","ta_in","te_in","tg_cyrl_tj",
            "th_th","tk_tm","tlh_qs","tn_za","tr_tr","tt_ru",
            "tzm_latn_dz","ug_cn","uk_ua","ur_pk","uz_cyrl_uz",
            "uz_latn_uz","uz_uz","vi_vn","wo_sn","xh_za","yo_ng",
            "zh_cn","zh_hk","zh_mo","zh_sg","zh_tw","zu_za",
            "pirate",
        };

        static constexpr String localeStringFull[] =
        {
            "Afrikaans (South Africa)","Amharic","Arabic (U.A.E.)","Arabic (Bahrain)",
            "Arabic (Algeria)","Arabic (Egypt)","Arabic (Iraq)","Arabic (Jordan)","Arabic (Kuwait)",
            "Arabic (Lebanon)","Arabic (Libya)","Arabic (Morocco)","Mapudungun","Arabic (Oman)",
            "Arabic (Qatar)","Arabic (Saudi Arabia)","Arabic (Sudan)","Arabic (Syria)",
            "Arabic (Tunisia)","Arabic (Yemen)","Assamese","Azeri (Latin)",
            "Azeri (Cyrillic)","Azeri (Latin)","Bashkir","Belarusian","Bulgarian","Bangla (Bangladesh)","Bangla (India)",
            "Tibetan","Breton (France)","Bosnian (Cyrillic)","Bosnian (Latin)","Catalan","Corsican (France)",
            "Czech","Welsh","Denmark","German (Austria)","German (Switzerland)","German (Germany)",
            "German (Liechtenstein)","German (Luxembourg)","Lower Sorbian (Germany)","Divehi","Greek (Cyprus)","Greek (Greece)",
            "English","English (Australia)","English (Belize)","English (Canada)","English (Caribbean)","English (Great Britain)",
            "English (Ireland)","English (Indonesia)","English (Jamaica)","English (Malta)","English (Malaysia)","English (New Zealand)",
            "English (Philippines)","English (Singapore)","English (Trinidad and Tobago)","English (United States)","English (South Africa)","English (Zimbabwe)",
            "Spanish (Argentina)","Spanish (Bolivia)","Spanish (Chile)","Spanish (Colombia)","Spanish (Costa Rica)","Spanish (Dominican Republic)","Spanish (Ecuador)","Spanish (Castilian)","Spanish (Guatemala)","Spanish (Honduras)","Spanish (Mexico)",
            "Spanish (Nicaragua)","Spanish (Panama)","Spanish (Peru)","Spanish (Puerto Rico)","Spanish (Paraguay)","Spanish (El Salvador)",
            "Spanish (United States)","Spanish (Uruguay)","Spanish (Venezuela)","Estonian","Basque","Farsi",
            "Finnish","Filipino (Philippines)","Faroese","French (Belgium)","French (Canada/Quebec)","French (Switzerland)",
            "French (France)","French (Luxembourg)","French (Monaco)","Frisian (Netherlands)","Irish","Scottish Gaelic (Great Britain)",
            "Scottish Gaelic","Galician","Alsatian (France)","Gujarati","Hausa Latin (Nigeria)","Hebrew",
            "Hindi","Croatian (Bosnia and Herzegovina)","Croatian (Croatia)","Upper Sorbian (Germany)","Hungarian","Armenian",
            "Indonesian","Igbo","Yi","Indonesian","Icelandic","Italian (Switzerland)",
            "Italian (Italy)","Inuktitut Syllabics (Canada)","Inuktitut Latin (Canada)","Inuktitut (Canada)","Japanese","Georgian",
            "Kazakh","Greenlandic","Khmer","Kannada","Konkani","Korean",
            "Kyrgyz","Luxembourgish","Lao","Lithuanian","Latvian","Maori",
            "Macedonian (FYROM/North Macedonia)","Malayalam","Mongolian","Mongolian Traditional (China)","Mohawk","Marathi",
            "Malay (Brunei)","Malay (Malaysia)","Maltese","Norwegian","Nepali","Dutch (Belgium)",
            "Dutch (Netherlands)","Norwegian (Nynorsk)","","Sesotho se Leboa","Occitan (France)","Odia","Punjabi",
            "Polish","Dari","Pashto","Portuguese (Brazil)","Portuguese (Portugal)","",
            "Quechua (Bolivia)","Quechua (Ecuador)","Quechua (Peru)","Romansh (Switzerland)","Romanian (Moldova)","Romanian (Romania)","",
            "Russian (Russia)","Rwandan","Sakha (Russia)","Sanskrit","Sami (Finland)","Sami (Norway)",
            "Sami (Sweden)","Sri Lankan","Slovak","Slovenian","Sami (Southern, Norway)","Sami (Southern, Sweden)",
            "Sami (Lule, Norway)","Sami (Lule, Sweden)","Inari Sami (Finland)","Sami (Skolt, Finland)","Albanian","Serbian (Bosnia and Herzegovina)",
            "Serbian (Serbia)","Serbian Cyrillic (Bosnia and Herzegovina)","Serbian Cyrillic (Serbia)","Serbian Cyrillic (Montenegro)","Serbian Cyrillic (Serbia)","Serbian Latin (Bosnia and Herzegovina)",
            "Serbian Latin (Serbia)","Serbian Latin (Montenegro)","Serbian Latin (Serbia)","Serbian (Montenegro)","Serbian (Serbia)","Serbian (Serbia and Monenegro)",
            "Swedish (Finland)","Swedish (Sweden)","Swahili","Syriac","Tamil","Telugu",
            "Tajik Cyrillic","Thai","Turkmen","","Tswana","Turkish","Tatar",
            "Tamazight Latin","Uyghur (China)","Ukrainian","Urdu","Uzbek Cyrillic","Uzbek Latin",
            "Uzbek","Vietnamese","Wolof","Xhosa","Yoruba","Chinese (China)",
            "Chinese (Hong Kong)","Chinese (Macau)","Chinese (Singapore)","Chinese (Taiwan/Republic of China/Chinese Taipei)","Zulu","Pirate",
        };

        using Container = std::vector<std::pair<std::string, std::string>>;
        const FString& getLocaleString(String original, LocaleTypes locale) noexcept;
        std::array<Container, static_cast<int>(LocaleTypes::pirate) + 1> translations{};

        LocaleTypes defaultLayout = LocaleTypes::en_US;
        LocaleTypes currentLayout = LocaleTypes::en_US;
        FString emptyString;
    };

    class UVK_PUBLIC_API Locale
    {
    public:
        static constexpr const char* getLocaleName(LocaleTypes types, bool bShort) noexcept;
        static LocaleTypes getLocaleID(const FString& str) noexcept;

        [[maybe_unused]] static FString& getLocaleString(String original, LocaleTypes locale) noexcept;
        [[maybe_unused]] static LocaleTypes& getCurrentLayout() noexcept;
        [[maybe_unused]] static LocaleTypes& getFallbackLayout() noexcept;
    };
}
