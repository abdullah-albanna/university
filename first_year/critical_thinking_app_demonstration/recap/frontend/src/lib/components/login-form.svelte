<script lang="ts">
	import { Button } from '$lib/components/ui/button/index.js';
	import * as Card from '$lib/components/ui/card/index.js';
	import { Input } from '$lib/components/ui/input/index.js';
	import { Label } from '$lib/components/ui/label/index.js';

	let {
		accounts,
		setLoggedin
	}: {
		accounts: { email: string; email: string }[];
		setLoggedin: () => void;
	} = $props();

	let email = $state('');
	let password = $state('');

	function login(): void {
		if (accounts.some((acc) => acc.password == password && acc.email == email)) {
			setLoggedin();
		} else {
			console.error('not there');
		}
	}
</script>

<Card.Root class="mx-auto max-w-sm">
	<Card.Header>
		<Card.Title class="text-2xl">Login</Card.Title>
		<Card.Description>Enter your email below to login to your account</Card.Description>
	</Card.Header>
	<Card.Content>
		<div class="grid gap-4">
			<div class="grid gap-2">
				<Label for="email">Email</Label>
				<Input id="email" type="email" bind:value={email} placeholder="m@example.com" required />
			</div>
			<div class="grid gap-2">
				<div class="flex items-center">
					<Label for="password">Password</Label>
					<a href="##" class="ml-auto inline-block text-sm underline"> Forgot your password? </a>
				</div>
				<Input id="password" type="password" bind:value={password} required />
			</div>
			<Button type="button" onclick={login} class="w-full">Login</Button>
		</div>
		<div class="mt-4 text-center text-sm">
			Don't have an account?
			<a href="/signup" class="underline"> Sign up </a>
		</div>
	</Card.Content>
</Card.Root>
