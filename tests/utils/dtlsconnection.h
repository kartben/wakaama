/*******************************************************************************
 *
 * Copyright (c) 2015 Intel Corporation and others.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * The Eclipse Distribution License is available at
 *    http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Simon Bernard - initial API and implementation
 *
 *******************************************************************************/

#ifndef DTLS_CONNECTION_H_
#define DTLS_CONNECTION_H_

#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdbool.h>

#include "tinydtls/tinydtls.h"
#include "tinydtls/dtls.h"
#include "liblwm2m.h"


typedef struct _dtls_connection_t
{
    struct _dtls_connection_t *  next;
    int                     sock;
    struct sockaddr_in6     addr;
    size_t                  addrLen;
    session_t *      dtlsSession;
    lwm2m_object_t * securityObj;
    int securityInstId;
    lwm2m_context_t * lwm2mH;
    dtls_context_t * dtlsContext;
} dtls_connection_t;

int create_socket(const char * portStr);

dtls_connection_t * connection_find(dtls_connection_t * connList, const struct sockaddr_storage * addr, size_t addrLen);
dtls_connection_t * connection_new_incoming(dtls_connection_t * connList, int sock, const struct sockaddr * addr, size_t addrLen);
dtls_connection_t * connection_create(dtls_connection_t * connList, int sock, lwm2m_object_t * securityObj, int instanceId, lwm2m_context_t * lwm2mH);

void connection_free(dtls_connection_t * connList);

int connection_send(dtls_connection_t *connP, uint8_t * buffer, size_t length);
int connection_handle_packet(dtls_connection_t *connP, uint8_t * buffer, size_t length);

#endif
