<script lang="ts">
	import { goto } from '$app/navigation';
	import { Button } from '$lib/components/ui/button/index.js';
	import * as Card from '$lib/components/ui/card/index.js';
	import { Input } from '$lib/components/ui/input/index.js';
	import { Label } from '$lib/components/ui/label/index.js';
	import * as Dialog from '$lib/components/ui/dialog/index.js';
	import { ScrollArea } from '$lib/components/ui/scroll-area/index.js';

	const {
		addAccount,
		setSignedup
	}: {
		addAccount: (account: { email: string; password: string }) => void;
		setSignedup: () => void;
	} = $props();

	let email = $state('');
	let password = $state('');
	let confirmPassword = $state('');
	let error = $state('');

	const createAccount = async () => {
		error = '';

		if (!email || !password || !confirmPassword) {
			error = 'All fields are required';
			return;
		}
		if (password !== confirmPassword) {
			error = 'Passwords do not match';
			return;
		}

		try {
			addAccount({ email, password });
			setSignedup();
			await goto('/');
		} catch (err) {
			console.error(err);
		}
	};

	const termsText = `1. Overview & Acceptance

By installing or using “Point-and-Watch” (the “App”), you agree to these Terms of Service (“Terms”) in full. No take-backsies—read carefully. If you don’t agree, uninstall now and peace out.


2. Who You Are

You promise that you’re old enough to consent (usually 13+ in most places) and that you’re not using stolen payment methods or impersonating a pineapple.


3. What You Get (License Grant)

We give you a limited, non-exclusive, revocable license to use the App on your personal computer. Don’t redistribute, decompile, reverse-engineer, or pretend it’s your idea.


4. What You Don’t Get (Restrictions)

No sneaking around:

    Don’t rent, lease, sublicense or time-share the App.

    Don’t modify, copy, adapt, translate, or create derivative works.

    Don’t bypass or tamper with any security features.


5. Intellectual Property

All rights, titles, and interests in the App and its content (code, graphics, logos, trade-secrets, jokes) belong to us. You get a license to enjoy it, nothing more.


6. User Conduct & Obligations

    Use the App responsibly—no feeding it malware or using it to break the speed of light.

    Keep your login credentials to yourself. If they leak, you’re on your own.

    Report any bugs, glitches, or gremlins you discover; we’ll try to fix them but can’t promise a unicorn.


7. Termination

We can suspend or terminate your license for any reason, including but not limited to:

    You act shady.

    You violate these Terms.

    We need more room on our servers.
    If your account’s terminated, you lose access. No refunds, no take-backs.


8. Disclaimers & Warranties

The App is provided “as is” and “as available.” We disclaim all warranties—express, implied, statutory—including merchantability, fitness for a particular purpose, and “won’t crash when you need it most.”


9. Limitation of Liability

Under no circumstances will we be liable for any direct, indirect, special, incidental, or consequential damages, loss of data, profits, or goodwill, even if we knew they might happen. Basically, if your cat walks over your keyboard mid-screenshot and deletes your novel, don’t blame us.


10. Indemnification

You agree to defend, indemnify, and hold us harmless from any claims, damages, losses, or expenses (including attorneys’ fees) arising from your use of the App or your violation of these Terms.


11. Changes to the Terms

We reserve the right to tweak these Terms whenever we feel like it. We’ll post updates in the App or here: terms.pointandwatch.example. It’s your job to check back. Continued use = you accept the new Terms.


12. Governing Law & Disputes

These Terms are governed by the laws of the Republic of Everywhere. Any disputes go to arbitration—no jury dramas, no class actions, unless your country mandates otherwise.


13. Privacy & Data Capture Notice

By using the App, you acknowledge and accept that it will transparently take screenshots of your computer screen approximately every 10 seconds during runtime. These images may include sensitive content—your browser tabs, chat windows, and secret pizza-ordering habits.

14. Contact Us

Questions, concerns, or want to vent? Email us at legal@pointandwatch.example or send a carrier pigeon to 123 Screenshot Lane.`;

	const policyText = `1. Introduction

We value transparency. This Privacy Policy explains what data we collect, why we collect it, how we use it, and your rights regarding your data.


2. Data We Collect

    Screenshots: Automatic captures of your on-screen content every ~10 seconds while the App is active.

    Usage Metrics: Crash reports, feature usage stats, performance logs.

    Device Info: OS version, hardware model, available storage, timezone (to timestamp screenshots).


3. How We Use Your Data

    Demonstration & Analytics: To show exactly why reading policies matters.

    App Improvement: We analyze patterns in screenshots to understand UI issues or bugs.

    No Targeted Ads: We don’t use this data for ad profiling—Promise.


4. Data Sharing & Disclosure

    Service Providers: We may share data with cloud storage vendors or analytics platforms, under strict confidentiality.

    Legal Requirements: We’ll disclose data if legally compelled (court order, subpoena, or if our CEO really begs).

    No Sale of Your Data: Under no circumstance will we sell your screenshots or personal info to third-party marketers.


5. Data Retention

    Screenshots and logs are stored for up to 30 days, then automatically deleted.

    Summary analytics (no images) may be kept for internal research up to 2 years.


6. Security Measures

We use industry-standard encryption at rest and in transit, frequent vulnerability scans, and a team of vigilant code-review ninjas to protect your data. But, let’s be real—no system is bulletproof.


7. Your Rights

    Access: Ask us for a copy of your screenshots and logs.

    Deletion: Request permanent deletion before the 30-day auto-delete hits.

    Questions or Complaints: Email privacy@pointandwatch.example.


8. Children’s Privacy

Our App is not directed at children under 13. We do not knowingly collect data from minors. If you’re under 13, don’t use the App—ask an adult.


9. Policy Updates

We might tweak this Policy to stay current. Changes take effect when posted and are identified by a revised “Last Updated” date at the top of this document.

Last Updated: April 24, 2025 (Asia/Aden timezone)`;
</script>

<Card.Root class="mx-auto max-w-sm">
	<Card.Header>
		<Card.Title class="text-2xl">Signup</Card.Title>
		<Card.Description>Enter your email below to create an account</Card.Description>
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
				</div>
				<Input id="password" type="password" bind:value={password} required />

				<div class="flex items-center">
					<Label for="password">Confirm Password</Label>
				</div>
				<Input id="password" type="password" bind:value={confirmPassword} required />
			</div>

			{#if error}
				<p class="text-center text-sm text-red-500">{error}</p>
			{/if}

			<Button type="button" onclick={createAccount} class="w-full">Signup</Button>
		</div>

		<div class="mt-4 text-center text-sm">
			Already have an account?
			<a href="/login" class="underline"> Login </a>
		</div>

		<!-- Terms and conditions checkbox block -->
		<div class="mt-4 flex items-start gap-3">
			<div class="space-y-1 text-sm leading-snug">
				<p class="text-muted-foreground">
					By signing up, you agree to our
					<Dialog.Root>
						<Dialog.Trigger>
							<a href="#" class="text-primary underline hover:text-primary/90">Terms of Service</a>
						</Dialog.Trigger>
						<Dialog.Content class="max-w-lg">
							<Dialog.Header>
								<Dialog.Title>Terms of Service</Dialog.Title>
								<Dialog.Description class="mt-4">
									<ScrollArea class="h-[60vh] w-full rounded-md border" orientation="both">
										{#each termsText.split('\n\n') as paragraph}
											<p class="min-w-full space-y-4 p-4 text-sm leading-relaxed">{paragraph}</p>
										{/each}
									</ScrollArea>
								</Dialog.Description>
							</Dialog.Header>
						</Dialog.Content>
					</Dialog.Root>
					and

					<Dialog.Root>
						<Dialog.Trigger>
							<a href="/#" class="text-primary underline hover:text-primary/90">Privacy Policy.</a>
						</Dialog.Trigger>
						<Dialog.Content class="max-w-lg">
							<Dialog.Header>
								<Dialog.Title>Privacy Policy</Dialog.Title>
								<Dialog.Description class="mt-4">
									<ScrollArea class="h-[60vh] w-full rounded-md border" orientation="both">
										{#each policyText.split('\n\n') as paragraph}
											<p class="min-w-full space-y-4 p-4 text-sm leading-relaxed">{paragraph}</p>
										{/each}
									</ScrollArea>
								</Dialog.Description>
							</Dialog.Header>
						</Dialog.Content>
					</Dialog.Root>
				</p>
			</div>
		</div>
	</Card.Content>
</Card.Root>
