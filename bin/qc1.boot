#! /bin/sh

swipl -x /home/pjr/qp_dev/rel/qp8.7/bin/qc1.boot.po -F none -f none -t halt -g "main(['$1'])"
