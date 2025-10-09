package main

import (
	"fmt"
	"strings"
)

type helloSession struct {
	name      string
	useClippy bool
}

func newHelloSession() *helloSession {
	return &helloSession{name: "World"}
}

func handleHelloCommand(session *helloSession, input string, commander r2Commander) (string, bool) {
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

	if strings.EqualFold(session.name, "clippy") {
		session.useClippy = true
	}

	if session.useClippy {
		if commander == nil {
			return fmt.Sprintf("Hello %s!\n", session.name), true
		}

		command := fmt.Sprintf("'?E Hello, %s", session.name)
		output, err := commander.Cmd(command)
		if err != nil {
			return fmt.Sprintf("Hello %s!\n", session.name), true
		}
		return output, true
	}

	return fmt.Sprintf("Hello %s!\n", session.name), true
}

func releaseHelloSession(*helloSession) {}

func main() {}
