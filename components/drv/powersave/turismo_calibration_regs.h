#include <soc_types.h>

ssv_cabrio_reg rf_calibration_result[]={
        //{0xccb0a474, 0},    //bt
        {0xccb0a478, 0},
        {0xccb0a470, 0},
        {0xccb0a404, 0},
        {0xccb0a418, 0},
        {0xccb0a564, 0},
        {0xccb0a4a0, 0},
        {0xccb0a4bc, 0},
        {0xccb0a460, 0},
        {ADR_WF_DCOC_IDAC_REGISTER1, 0},        // rxdc   
        {ADR_WF_DCOC_IDAC_REGISTER2, 0},    
        {ADR_WF_DCOC_IDAC_REGISTER3, 0},    
        {ADR_WF_DCOC_IDAC_REGISTER4, 0},    
        {ADR_WF_DCOC_IDAC_REGISTER5, 0},    
        {ADR_WF_DCOC_IDAC_REGISTER6, 0},    
        {ADR_WF_DCOC_IDAC_REGISTER7, 0},    
        {ADR_WF_DCOC_IDAC_REGISTER8, 0},    
  #if 0
        {ADR_BT1M_DCOC_IDAC_REGISTER1, 0},        // bt rxdc 
        {ADR_BT1M_DCOC_IDAC_REGISTER2, 0},    
        {ADR_BT1M_DCOC_IDAC_REGISTER3, 0},    
        {ADR_BT1M_DCOC_IDAC_REGISTER4, 0},    
        {ADR_BT1M_DCOC_IDAC_REGISTER5, 0},    
        {ADR_BT1M_DCOC_IDAC_REGISTER6, 0},    
        {ADR_BT1M_DCOC_IDAC_REGISTER7, 0},    
        {ADR_BT1M_DCOC_IDAC_REGISTER8, 0},    
   #endif
        {ADR_WF_TX_FILTER_DCOC_REGISTER, 0},    // txdc
        //{ADR_BT_TX_FILTER_DCOC_REGISTER, 0},    // bt txdc
        {ADR_TX_IQ_COMP_2G, 0},                 // txiq
        {ADR_RX_IQ_COMP_2G_20_40, 0},           // rxiq
        //{ADR_RX_IQ_COMP_BT, 0},                 // bt rxiq
        {ADR_WIFI_HT20_RX_FILTER_REGISTER, 0},  // rxrcbw20
        {ADR_WIFI_HT40_RX_FILTER_REGISTER, 0},  // rxrxbw40
        {ADR_WIFI_PADPD_2G_GAIN_REG0, 0},       // padpd
        {ADR_WIFI_PADPD_2G_GAIN_REG1, 0},
        {ADR_WIFI_PADPD_2G_GAIN_REG2, 0},
        {ADR_WIFI_PADPD_2G_GAIN_REG3, 0},
        {ADR_WIFI_PADPD_2G_GAIN_REG4, 0},
        {ADR_WIFI_PADPD_2G_GAIN_REG5, 0},
        {ADR_WIFI_PADPD_2G_GAIN_REG6, 0},
        {ADR_WIFI_PADPD_2G_GAIN_REG7, 0},
        {ADR_WIFI_PADPD_2G_GAIN_REG8, 0},
        {ADR_WIFI_PADPD_2G_GAIN_REG9, 0},
        {ADR_WIFI_PADPD_2G_GAIN_REGA, 0},
        {ADR_WIFI_PADPD_2G_GAIN_REGB, 0},
        {ADR_WIFI_PADPD_2G_GAIN_REGC, 0},
        {ADR_WIFI_NEW_PADPD_PHASE_REG0, 0},
        {ADR_WIFI_NEW_PADPD_PHASE_REG1, 0},
        {ADR_WIFI_NEW_PADPD_PHASE_REG2, 0},
        {ADR_WIFI_NEW_PADPD_PHASE_REG3, 0},
        {ADR_WIFI_NEW_PADPD_PHASE_REG4, 0},
        {ADR_WIFI_NEW_PADPD_PHASE_REG5, 0},
        {ADR_WIFI_NEW_PADPD_PHASE_REG6, 0},
        {ADR_WIFI_NEW_PADPD_PHASE_REG7, 0},
        {ADR_WIFI_NEW_PADPD_PHASE_REG8, 0},
        {ADR_WIFI_NEW_PADPD_PHASE_REG9, 0},
        {ADR_WIFI_NEW_PADPD_PHASE_REGA, 0},
        {ADR_WIFI_NEW_PADPD_PHASE_REGB, 0},
        {ADR_WIFI_NEW_PADPD_PHASE_REGC, 0},
        {ADR_WIFI_NEW_PADPD_PHASE_REGD, 0},
        {ADR_WIFI_NEW_PADPD_PHASE_REGE, 0},
        {ADR_WIFI_NEW_PADPD_PHASE_REGF, 0},
        {ADR_WIFI_PADPD_2G_CONTROL_REG, 0},
		{0xCCB0A88c, 0}, // by wifi/bt control
};

