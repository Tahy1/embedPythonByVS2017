#!/usr/bin/env python
# encoding:utf-8
# @author rikugun

# 帮助使用 python clob_demo.py "/data/*.log"的方式来执行

import cx_Oracle

def readDataFromOracle():
    host="127.0.0.1"
    port=1521
    dbname="orcl"
    dsn=cx_Oracle.makedsn(host, port, dbname)
    conn=cx_Oracle.connect('SYSTEM','8', dsn)
    cur = conn.cursor(conn)
    sql0 = 'SELECT "dd" FROM "lty" where "tt"=1'
    cur.execute(sql0)
    number = []
    time = []
    angle = []
    torque = []
    velocity = []
    step = []
    allData = []
    for row in cur:
        text = row[0].read()
        lines = text.split('\r\n')
        for l in lines:
            if '' != l:
                temp = ''.join(l.split('"')).split(';')
                number.append(int(temp[0]))
                time.append(float(temp[1]))
                angle.append(int(temp[2]))
                torque.append(float(temp[3]))
                velocity.append(int(temp[4]))
                step.append(int(temp[5]))
    cur.close()
    #conn.close()
    return number,time,angle,torque,velocity,step
