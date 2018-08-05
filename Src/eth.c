#include "eth.h"


void eth_send(char *str, size_t size){
    netconn_write(newconn, str, size, NETCONN_COPY);
} 

void tcpecho(void)
{
   // struct netconn *conn, *newconn;
    err_t err, accept_err;
    struct netbuf* buf;
    void* data;
    u16_t len;
    err_t recv_err;

    /* Create a new connection identifier. */
    conn = netconn_new(NETCONN_TCP);
    if (conn != NULL)
    {
        /* Bind connection to well known port number 80. */
        err = netconn_bind(conn, NULL, 80);

        if (err == ERR_OK)
        {
            /* Tell connection to go into listening mode. */
            netconn_listen(conn);

            while (1)
            {
                /* Grab new connection. */
                accept_err = netconn_accept(conn, &newconn);

                /* Process the new connection. */
                if (accept_err == ERR_OK)
                {
                    while ((recv_err = netconn_recv(newconn, &buf)) == ERR_OK)
                    {
                        do
                        {
                            netbuf_data(buf, &data, &len);
                            netconn_write(newconn, data, len, NETCONN_COPY);
                            command_handler(eth_send,data);
                            HAL_UART_Transmit(&huart3, data, len,100);

                        } while (netbuf_next(buf) >= 0);

                        netbuf_delete(buf);
                    }

                    /* Close connection and discard connection identifier. */
                    netconn_close(newconn);
                    netconn_delete(newconn);
                }
            }
        }
        else
        {
            netconn_delete(newconn);
            HAL_UART_Transmit(&huart3, " can not bind TCP netconn\n\r",27,100);
        }
    }
    else
    {
        HAL_UART_Transmit(&huart3, "can not create TCP netconn\n\r",28,100);
    }
}

void tcpcounter(void)
{
    struct netconn *conn, *newconn;
    err_t err, accept_err;
    /* Create a new connection identifier. */
    conn = netconn_new(NETCONN_TCP);
    if (conn != NULL)
    {
        /* Bind connection to well known port number 80. */
        err = netconn_bind(conn, NULL, 80);
        if (err == ERR_OK)
        {
            /* Tell connection to go into listening mode. */
            netconn_listen(conn);
            /* Grab new connection. */
            accept_err = netconn_accept(conn, &newconn);
            /* Process the new connection. */
            if (accept_err == ERR_OK)
            {
                while (1)
                {
                    char buffer[32] = { 0x00 };
                    memset(buffer, sizeof(buffer), 0x00);
                    static int cntr = 0;
                    sprintf(buffer, "Сounter = %d\r", cntr++);
                    netconn_write(
                        newconn, (const unsigned char*)buffer, strlen(buffer), NETCONN_COPY);
                    osDelay(1000);
                }
            }
        }
    }
}
