#!/usr/bin/env zsh

# This is a simplistic reimplementation of Kicksecure's sdwdate, in the form of a shell script.
# Cobalt sdwdate will randomly select 3 websites to fetch the date from and print out the average of all three dates.
# Unlike the original sdwdate, this script does not use Tor, and only prints a correctly formatted date without setting it.

# TODO: choose several servers randomly from sdwdate.servers
# TODO: average dates instead of using one

TARGET="https://cr.yp.to"

CURL_DATE=($(curl -v "${TARGET}" 2>&1 | tr '[:upper:]' '[:lower:]' | grep "< date")) # tr ... is to ensure that the date field is always lowercase (it sometimes isn't)

case "${CURL_DATE[5]}" in
	jan) MONTH=01;;
	feb) MONTH=02;;
	mar) MONTH=03;;
	apr) MONTH=04;;
	may) MONTH=05;;
	jun) MONTH=06;;
	jul) MONTH=07;;
	aug) MONTH=08;;
	sep) MONTH=09;;
	oct) MONTH=10;;
	nov) MONTH=11;;
	dec) MONTH=12;;
	*)
		echo "Date parsing error"
		exit 1
		;;
esac

DATE="$(echo ${CURL_DATE[7]} | sed 's/://' | sed 's/:/./')"

CURL_DATE="${CURL_DATE[6]}${MONTH}${CURL_DATE[4]}${DATE}"

echo "${CURL_DATE}" # In order to be set correctly, `date` must be used with the `-u` option to signal that this date is in UTC.
