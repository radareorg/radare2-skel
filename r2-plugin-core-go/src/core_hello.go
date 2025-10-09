package main

import (
	"fmt"
	"strings"
)

type helloSession struct {
	name string
}

func newHelloSession() *helloSession {
	return &helloSession{name: "World"}
}

func handleHelloCommand(session *helloSession, input string) (string, bool) {
	if session == nil {
		return "", false
	}

	cmd := strings.TrimSpace(input)
	if !strings.HasPrefix(cmd, "hello") {
		return "", false
	}

	args := strings.Fields(cmd)
	if len(args) > 1 {
		session.name = strings.Join(args[1:], " ")
	}

	return fmt.Sprintf("Hello %s!\n", session.name), true
}

func releaseHelloSession(*helloSession) {}

func main() {}
