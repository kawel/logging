/*
 * @file: logging_transport.h
 * @author: Paweł Kawula (pawel.kawula@kelectronics.pl)
 * -----
 * Copyright 2023 - KElectronics
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 */

#ifndef LOGGING_TRANSPORT_H
#define LOGGING_TRANSPORT_H


// #define SdkLog( string, ...) com_send_const_str(&trace_com, string)
// #define SdkLog(string) trace_string(string)
#define SdkLog( string, ...) log_function(&trace_com, string)

#endif /* LOGGING_TRANSPORT_H */
