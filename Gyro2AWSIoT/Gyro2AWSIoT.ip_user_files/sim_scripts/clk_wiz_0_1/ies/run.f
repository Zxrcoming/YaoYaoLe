-makelib ies_lib/xil_defaultlib -sv \
  "D:/vivado/Vivado/2019.1/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
-endlib
-makelib ies_lib/xpm \
  "D:/vivado/Vivado/2019.1/data/ip/xpm/xpm_VCOMP.vhd" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "../../../../Gyro2AWSIoT.srcs/sources_1/ip/clk_wiz_0_1/clk_wiz_0_clk_wiz.v" \
  "../../../../Gyro2AWSIoT.srcs/sources_1/ip/clk_wiz_0_1/clk_wiz_0.v" \
-endlib
-makelib ies_lib/xil_defaultlib \
  glbl.v
-endlib

