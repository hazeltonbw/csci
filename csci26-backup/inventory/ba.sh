#!/bin/bash

i=0

until [ $i -gt 1000 ]
do
	echo CREATE TABLE $i >> inputfile0
	echo INSERT INTO $i VALUES A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z >> inputfile0
	((i=i+1))
done
