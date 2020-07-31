set_property SRC_FILE_INFO {cfile:D:/shixi/SEA-master-latest/SEA-master/Demos/2.IoT/Gyro2AWSloT/FPGA_Project/system.xdc rfile:../../../../SEA-master-latest/SEA-master/Demos/2.IoT/Gyro2AWSloT/FPGA_Project/system.xdc id:1} [current_design]
set_property src_info {type:XDC file:1 line:3 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN H4  IOSTANDARD LVCMOS33 } [get_ports { clk_100MHz }]; #IO_L13P_T2_MRCC_35 Sch=sysclk
set_property src_info {type:XDC file:1 line:9 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN P12 IOSTANDARD LVCMOS33} [get_ports Gyro_IIC_SCL];
set_property src_info {type:XDC file:1 line:10 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN P13 IOSTANDARD LVCMOS33} [get_ports Gyro_IIC_SDA];
set_property src_info {type:XDC file:1 line:15 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN H1 IOSTANDARD LVCMOS33} [get_ports VCC];
set_property src_info {type:XDC file:1 line:16 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN H2 IOSTANDARD LVCMOS33} [get_ports GND];
set_property src_info {type:XDC file:1 line:18 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN N4  IOSTANDARD LVCMOS33} [get_ports IIC_OE];
set_property src_info {type:XDC file:1 line:19 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN L13 IOSTANDARD LVCMOS33} [get_ports VCCEN];
set_property src_info {type:XDC file:1 line:22 export:INPUT save:INPUT read:READ} [current_design]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets {I_qspi_clk_IBUF}]
set_property src_info {type:XDC file:1 line:23 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN P2 IOSTANDARD LVCMOS33}  [get_ports {qspi_d0}]
set_property src_info {type:XDC file:1 line:24 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN L14 IOSTANDARD LVCMOS33} [get_ports {qspi_d1}]
set_property src_info {type:XDC file:1 line:25 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN J13 IOSTANDARD LVCMOS33} [get_ports {qspi_d2}]
set_property src_info {type:XDC file:1 line:26 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN D13 IOSTANDARD LVCMOS33} [get_ports {qspi_d3}]
set_property src_info {type:XDC file:1 line:27 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN M13 IOSTANDARD LVCMOS33} [get_ports {I_qspi_cs}]
set_property src_info {type:XDC file:1 line:28 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN H14 IOSTANDARD LVCMOS33} [get_ports {I_qspi_clk}]
