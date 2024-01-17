#!/usr/bin/env zsh

# Script for randomly generating a Windows-esque hostname

RANDLEN=0
RANDO=
while [[ "${RANDLEN}" -lt 7 ]]; do
	RANDCHAR=$(printf %s $(unicode $(jot -r 1 16 127)))
	TR=$(echo ${RANDCHAR} | tr -cd '0-9A-Z')
	if [[ ! -z ${RANDCHAR} && ${TR} == ${RANDCHAR} ]]; then
		RANDLEN="$(expr ${RANDLEN} + 1)"
		RANDO="${RANDO}${RANDCHAR}"
	fi
done
HOSTNAME="Desktop-${RANDO}"
echo "${HOSTNAME}"
