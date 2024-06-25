## Setup

`wget https://golang.org/dl/go1.16.5.linux-amd64.tar.gz`

`sudo tar -C /usr/local -xzf go1.16.5.linux-amd64.tar.gz`

`nano ~/.profile`

`export PATH=$PATH:/usr/local/go/bin`

`source ~/.profile`

`go version`

## Build

`go run demo.go`

`go build demo.go`

`./demo`
