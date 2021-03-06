#include "cfg_eeprom.h"
#include "Arduino.h"
#include "EEPROM.h"
#include "esp_camera.h"
#include "debug.h"

#define EEPROM_SEPARATOR ':'
#define RESTORE_EEPROM_DEFAULT_FLAG 55

static cfg_struct cfg;
static int address = 0;

boolean initCfgFromEEPROM();
void storeCAMX(uint8_t n);
void loadCAMX(uint8_t n);
struct cfg_struct* get_current_cfg();
void storeCfgToEEPROM();
void restoreCfgFromEEPROM();
void storeParameterToEEPROM(String tmp);
String restoreParameterFromEEPROM();
void eraseEEPROM();
void storeDefaultCfgToEEPROM();

////////           Public method         /////////
struct cfg_struct* get_current_cfg(){
    return &cfg;
}

boolean initCfgFromEEPROM(){
    EEPROM.begin(EEPROM_SIZE);
	restoreCfgFromEEPROM();
    if ((cfg.RestoreDefaultFalg!= RESTORE_EEPROM_DEFAULT_FLAG)||(cfg.eepromUsed==EEPROM_SIZE-1)){
        eraseEEPROM();
		storeDefaultCfgToEEPROM();
        return false;
    }
    return true;
}

void storeCfgToEEPROM()
{
	address = 0;
	int n = 0;
	storeParameterToEEPROM((String)cfg.RestoreDefaultFalg);
	storeParameterToEEPROM(cfg.AP_WiFi_ssid);
	storeParameterToEEPROM(cfg.AP_WiFi_pw);
	storeParameterToEEPROM(cfg.WiFi_ssid);
	storeParameterToEEPROM(cfg.WiFi_pw);
	storeParameterToEEPROM((String)cfg.StartAPOnly);
	storeParameterToEEPROM((String)cfg.AutoStartTimeLapsStartUp);
	storeParameterToEEPROM((String)cfg.AutoStartCFG);
	storeParameterToEEPROM((String)cfg.TimeLapsDelta);
	storeParameterToEEPROM((String)cfg.forceFlash);
	storeParameterToEEPROM((String)cfg.forceFlashThresh);
	storeParameterToEEPROM((String)cfg.flash);
	storeParameterToEEPROM((String)cfg.flashThresh);
	for (n=0; n < NB_CAMERA_STORE; n++){
		storeParameterToEEPROM((String)cfg.camera[n].framesize);
		storeParameterToEEPROM((String)cfg.camera[n].quality);
		storeParameterToEEPROM((String)cfg.camera[n].brightness);
		storeParameterToEEPROM((String)cfg.camera[n].contrast);
		storeParameterToEEPROM((String)cfg.camera[n].saturation);
		storeParameterToEEPROM((String)cfg.camera[n].sharpness);
		storeParameterToEEPROM((String)cfg.camera[n].denoise);
		storeParameterToEEPROM((String)cfg.camera[n].special_effect);
		storeParameterToEEPROM((String)cfg.camera[n].wb_mode);
		storeParameterToEEPROM((String)cfg.camera[n].awb);
		storeParameterToEEPROM((String)cfg.camera[n].awb_gain);
		storeParameterToEEPROM((String)cfg.camera[n].aec);
		storeParameterToEEPROM((String)cfg.camera[n].aec2);
		storeParameterToEEPROM((String)cfg.camera[n].ae_level);
		storeParameterToEEPROM((String)cfg.camera[n].aec_value);
		storeParameterToEEPROM((String)cfg.camera[n].agc);
		storeParameterToEEPROM((String)cfg.camera[n].agc_gain);
		storeParameterToEEPROM((String)cfg.camera[n].gainceiling);
		storeParameterToEEPROM((String)cfg.camera[n].bpc);
		storeParameterToEEPROM((String)cfg.camera[n].wpc);
		storeParameterToEEPROM((String)cfg.camera[n].raw_gma);
		storeParameterToEEPROM((String)cfg.camera[n].lenc);
		storeParameterToEEPROM((String)cfg.camera[n].hmirror);
		storeParameterToEEPROM((String)cfg.camera[n].vflip);
		storeParameterToEEPROM((String)cfg.camera[n].dcw);
		storeParameterToEEPROM((String)cfg.camera[n].colorbar);
		storeParameterToEEPROM((String)cfg.camera[n].xclk_freq_hz);
		storeParameterToEEPROM((String)cfg.camera[n].flash);
		storeParameterToEEPROM((String)cfg.camera[n].flashThresh);
	}
	for (n=0; n < NB_COORD_STORE; n++){
		storeParameterToEEPROM((String)cfg.servoCoord[n].xPos);
		storeParameterToEEPROM((String)cfg.servoCoord[n].yPos);
	}
	storeParameterToEEPROM((String)cfg.servoXInv);
	storeParameterToEEPROM((String)cfg.servoYInv);
	storeParameterToEEPROM((String)cfg.useTrajectory);
	storeParameterToEEPROM((String)cfg.nbPicTrajectory);

	EEPROM.commit();
	cfg.eepromUsed = address;
}

void restoreCfgFromEEPROM()
{
	address = 0;
	int n = 0;
	cfg.RestoreDefaultFalg = atoi(restoreParameterFromEEPROM().c_str());
	cfg.AP_WiFi_ssid = restoreParameterFromEEPROM();
	cfg.AP_WiFi_pw= restoreParameterFromEEPROM();
	cfg.WiFi_ssid= restoreParameterFromEEPROM();
	cfg.WiFi_pw= restoreParameterFromEEPROM();
	cfg.StartAPOnly= atoi(restoreParameterFromEEPROM().c_str());
	cfg.AutoStartTimeLapsStartUp= atoi(restoreParameterFromEEPROM().c_str());
	cfg.AutoStartCFG = atoi(restoreParameterFromEEPROM().c_str());
	cfg.TimeLapsDelta= atoi(restoreParameterFromEEPROM().c_str());
	cfg.forceFlash= atoi(restoreParameterFromEEPROM().c_str());
	cfg.forceFlashThresh= atoi(restoreParameterFromEEPROM().c_str());
	cfg.flash= atoi(restoreParameterFromEEPROM().c_str());
	cfg.flashThresh= atoi(restoreParameterFromEEPROM().c_str());
	
	for (n=0; n < NB_CAMERA_STORE; n++){
		cfg.camera[n].framesize = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].quality = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].brightness = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].contrast = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].saturation = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].sharpness = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].denoise = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].special_effect = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].wb_mode = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].awb = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].awb_gain = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].aec = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].aec2 = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].ae_level = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].aec_value = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].agc = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].agc_gain = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].gainceiling = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].bpc = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].wpc = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].raw_gma = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].lenc = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].hmirror = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].vflip = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].dcw = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].colorbar = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].xclk_freq_hz = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].flash = atoi(restoreParameterFromEEPROM().c_str());
		cfg.camera[n].flashThresh = atoi(restoreParameterFromEEPROM().c_str());
	}
	for (n=0; n < NB_COORD_STORE; n++){
		cfg.servoCoord[n].xPos =  atoi(restoreParameterFromEEPROM().c_str());
		cfg.servoCoord[n].yPos =  atoi(restoreParameterFromEEPROM().c_str());
	}
	cfg.servoXInv =  atoi(restoreParameterFromEEPROM().c_str());
	cfg.servoYInv =  atoi(restoreParameterFromEEPROM().c_str());
	cfg.useTrajectory =  atoi(restoreParameterFromEEPROM().c_str());
	cfg.nbPicTrajectory =  atoi(restoreParameterFromEEPROM().c_str());
	
	//LOAD CRITICAL DEFAULT PARAMETERS
	if (cfg.AP_WiFi_ssid == ""){
		 cfg.AP_WiFi_ssid = "ESP32_CAM";
	}
	if (cfg.AP_WiFi_pw == ""){
		 cfg.AP_WiFi_pw = "thereisnospoon";
	}
	cfg.eepromUsed = address;
}

void storeDefaultCfgToEEPROM()
{
	address = 0;
	int n = 0;
	cfg.RestoreDefaultFalg = RESTORE_EEPROM_DEFAULT_FLAG;
	cfg.AP_WiFi_ssid = "ESP32_CAM";
	cfg.AP_WiFi_pw = "thereisnospoon";
	cfg.WiFi_ssid = " ";
	cfg.WiFi_pw = " ";
	cfg.StartAPOnly = true;
	cfg.AutoStartTimeLapsStartUp = false;
	cfg.AutoStartCFG = 0;
	cfg.TimeLapsDelta = 5;
	cfg.forceFlash = 0;
	cfg.forceFlashThresh = 0;
	cfg.flash = 0;
	cfg.flashThresh = 0;
	for (n=0; n < NB_CAMERA_STORE; n++){
		cfg.camera[n].framesize = 10;
		cfg.camera[n].quality = 10;
		cfg.camera[n].brightness = 0;
		cfg.camera[n].contrast = 0;
		cfg.camera[n].saturation = 0;
		cfg.camera[n].sharpness = 0;
		cfg.camera[n].denoise = 0; // not used
		cfg.camera[n].special_effect = 0;
		cfg.camera[n].wb_mode = 0;
		cfg.camera[n].awb = 1;
		cfg.camera[n].awb_gain = 1;
		cfg.camera[n].aec = 1;
		cfg.camera[n].aec2 = 0;
		cfg.camera[n].ae_level = 0;
		cfg.camera[n].aec_value = 168;
		cfg.camera[n].agc = 1;
		cfg.camera[n].agc_gain = 0;
		cfg.camera[n].gainceiling = 0;
		cfg.camera[n].bpc = 0;
		cfg.camera[n].wpc = 1;
		cfg.camera[n].raw_gma = 1;
		cfg.camera[n].lenc = 1;
		cfg.camera[n].hmirror = 0;
		cfg.camera[n].vflip = 0;
		cfg.camera[n].dcw = 1;
		cfg.camera[n].colorbar = 0;
		cfg.camera[n].xclk_freq_hz = 5000000;
		cfg.camera[n].flash = 0;
		cfg.camera[n].flashThresh = 0;
	}	
	for (n=0; n < NB_COORD_STORE; n++){
		cfg.servoCoord[n].xPos = 0;
		cfg.servoCoord[n].yPos = 0;
	}
	cfg.servoXInv = 0;
	cfg.servoYInv = 0;
	cfg.useTrajectory = 0;
	cfg.nbPicTrajectory = 200;
	storeCfgToEEPROM();
	cfg.eepromUsed = address;
}

void storeCAMX(uint8_t n)
{
	sensor_t *s = esp_camera_sensor_get();
	cfg.camera[n].framesize      = s->status.framesize;
	cfg.camera[n].quality        = s->status.quality;
	cfg.camera[n].brightness     = s->status.brightness;
	cfg.camera[n].contrast       = s->status.contrast;
	cfg.camera[n].saturation     = s->status.saturation;
	cfg.camera[n].sharpness      = s->status.sharpness;
	cfg.camera[n].denoise        = s->status.denoise;
	cfg.camera[n].special_effect = s->status.special_effect;
	cfg.camera[n].wb_mode        = s->status.wb_mode;
	cfg.camera[n].awb            = s->status.awb;
	cfg.camera[n].awb_gain       = s->status.awb_gain;
	cfg.camera[n].aec            = s->status.aec;
	cfg.camera[n].aec2           = s->status.aec2;
	cfg.camera[n].ae_level       = s->status.ae_level;
	cfg.camera[n].aec_value      = s->status.aec_value;
	cfg.camera[n].agc            = s->status.agc;
	cfg.camera[n].agc_gain       = s->status.agc_gain;
	cfg.camera[n].gainceiling    = s->status.gainceiling;
	cfg.camera[n].bpc            = s->status.bpc;
	cfg.camera[n].wpc            = s->status.wpc;
	cfg.camera[n].raw_gma        = s->status.raw_gma;
	cfg.camera[n].lenc           = s->status.lenc;
	cfg.camera[n].hmirror        = s->status.hmirror;
	cfg.camera[n].vflip          = s->status.vflip;
	cfg.camera[n].dcw            = s->status.dcw;
	cfg.camera[n].colorbar       = s->status.colorbar;
	cfg.camera[n].xclk_freq_hz   = s->xclk_freq_hz;
	cfg.camera[n].flash   		  = cfg.flash;
	cfg.camera[n].flashThresh	  = cfg.flashThresh;
}

void loadCAMX(uint8_t n)
{
	sensor_t *s = esp_camera_sensor_get();
	s->set_framesize(s, (framesize_t)cfg.camera[n].framesize);
	s->set_quality(s, cfg.camera[n].quality);
	s->set_brightness(s, cfg.camera[n].brightness);
	s->set_contrast(s, cfg.camera[n].contrast);
	s->set_saturation(s, cfg.camera[n].saturation);
	//sharpness
	//denoise
	s->set_special_effect(s, cfg.camera[n].special_effect);
	s->set_wb_mode(s, cfg.camera[n].wb_mode);
	s->set_whitebal(s, cfg.camera[n].awb);
	s->set_awb_gain(s, cfg.camera[n].awb_gain);
	s->set_exposure_ctrl(s, cfg.camera[n].aec);
	s->set_aec2(s, cfg.camera[n].aec2);
	s->set_ae_level(s, cfg.camera[n].ae_level);
	s->set_aec_value(s, cfg.camera[n].aec_value);
	s->set_gain_ctrl(s, cfg.camera[n].agc);
	s->set_agc_gain(s, cfg.camera[n].agc_gain);
	s->set_gainceiling(s, (gainceiling_t)cfg.camera[n].gainceiling);
	s->set_bpc(s, cfg.camera[n].bpc);
	s->set_wpc(s, cfg.camera[n].wpc);
	s->set_raw_gma(s, cfg.camera[n].raw_gma);
	s->set_lenc(s, cfg.camera[n].lenc);
	s->set_hmirror(s, cfg.camera[n].hmirror);
	s->set_vflip(s, cfg.camera[n].vflip);
	s->set_dcw(s, cfg.camera[n].dcw);
	s->set_colorbar(s, cfg.camera[n].colorbar);
	cfg.flash = cfg.camera[n].flash;
	cfg.flashThresh = cfg.camera[n].flashThresh;
	//xclk_freq_hz
}

////////           private method         /////////
void storeParameterToEEPROM(String tmp)
{
	int i=0;
	char myChar = ' ';
	for (i=0;i<tmp.length();i++)
	{
		myChar = char(tmp.charAt(i));
		EEPROM.write(address, byte(myChar));
		if (address < EEPROM_SIZE-1) {
		address = address + 1;
		}
	}
	if (address < EEPROM_SIZE-1) {
		EEPROM.write(address, byte(EEPROM_SEPARATOR));
		address = address + 1;
	}
}

String restoreParameterFromEEPROM()
{
	String tmp = "" ;
	while (EEPROM.read(address) != EEPROM_SEPARATOR && (address < EEPROM_SIZE-1)){
		tmp += (String)char(EEPROM.read(address));
		address = address + 1;
	}
	
	if (EEPROM.read(address) == EEPROM_SEPARATOR){
		if (address < EEPROM_SIZE-1){
				address = address + 1;
		}
	}
	else{
		tmp="";
	}
	return tmp;
}

void eraseEEPROM()
{
	for (address=0;address <= EEPROM_SIZE ;address++)
	{
		EEPROM.write(address, (uint8_t)0);
	}
	EEPROM.commit();
}