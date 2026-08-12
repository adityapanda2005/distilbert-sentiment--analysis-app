#!/bin/bash
CERTIFIER_ROOT=/home/aditya/certifier-framework-for-confidential-computing
SENTIMENT_DIR=$CERTIFIER_ROOT/sample_apps/sentiment_app
CERTIFIER_SERVICE=$CERTIFIER_ROOT/certifier_service/simpleserver
DOMAIN=datica-test

echo "=== Starting Certifier Service ==="
cd $SENTIMENT_DIR/service
$CERTIFIER_SERVICE \
    --policy_key_file=policy_key_file.$DOMAIN \
    --policy_cert_file=policy_cert_file.$DOMAIN \
    --policyFile=policy.bin \
    --readPolicy=true &
SERVER_PID=$!
sleep 2

echo "=== Certifying and running app1 (server role) ==="
cd $SENTIMENT_DIR
./sentiment_app.exe \
    --data_dir=./app1_data/ \
    --operation=cold-init \
    --measurement_file=example_app.measurement \
    --policy_store_file=policy_store.$DOMAIN \
    --policy_cert_file=policy_cert_file.$DOMAIN

./sentiment_app.exe \
    --data_dir=./app1_data/ \
    --operation=get-certified \
    --measurement_file=example_app.measurement \
    --policy_store_file=policy_store.$DOMAIN \
    --policy_cert_file=policy_cert_file.$DOMAIN

./sentiment_app.exe \
    --data_dir=./app1_data/ \
    --operation=run-app-as-server \
    --policy_store_file=policy_store.$DOMAIN &
APP_SERVER_PID=$!
sleep 2

echo "=== Running app2 (client role — sends text for sentiment analysis) ==="
cd $SENTIMENT_DIR
./sentiment_app.exe \
    --data_dir=./app2_data/ \
    --operation=cold-init \
    --measurement_file=example_app.measurement \
    --policy_store_file=policy_store.$DOMAIN \
    --policy_cert_file=policy_cert_file.$DOMAIN

./sentiment_app.exe \
    --data_dir=./app2_data/ \
    --operation=get-certified \
    --measurement_file=example_app.measurement \
    --policy_store_file=policy_store.$DOMAIN \
    --policy_cert_file=policy_cert_file.$DOMAIN

./sentiment_app.exe \
    --data_dir=./app2_data/ \
    --operation=run-app-as-client \
    --policy_store_file=policy_store.$DOMAIN

echo "=== Done ==="
kill $APP_SERVER_PID 2>/dev/null
kill $SERVER_PID 2>/dev/null
